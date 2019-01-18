#include "cartographer/cloud/internal/handlers/get_cloud_trajectory_state_handler.h"

#include "async_grpc/rpc_handler.h"
#include "cartographer/cloud/internal/map_builder_context_interface.h"
#include "cartographer/cloud/proto/map_builder_service.pb.h"
#include "cartographer/common/make_unique.h"

namespace cartographer {
namespace cloud {
namespace handlers {

// If trajectory not found in cloud, check return value to validate

void GetCloudTrajectoryStateHandler::OnRequest(const proto::GetCloudTrajectoryStateRequest& request) {
  if (!GetContext<MapBuilderContextInterface>()->CheckClientIdForTrajectory(
          request.client_id(), request.trajectory_id())) {
    LOG(ERROR) << "Unknown trajectory with ID " << request.trajectory_id()
               << " and client_id " << request.client_id();
    Finish(::grpc::Status(::grpc::NOT_FOUND, "Unknown trajectory"));
    return;
  }
  Send(common::make_unique<google::protobuf::Empty>());
}

}  // namespace handlers
}  // namespace cloud
}  // namespace cartographer
