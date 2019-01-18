#ifndef CARTOGRAPHER_CLOUD_INTERNAL_HANDLERS_GET_CLOUD_TRAJECTORY_STATE_HANDELR_H
#define CARTOGRAPHER_CLOUD_INTERNAL_HANDLERS_GET_CLOUD_TRAJECTORY_STATE_HANDELR_H

#include "async_grpc/rpc_handler.h"
#include "cartographer/cloud/proto/map_builder_service.pb.h"
#include "google/protobuf/empty.pb.h"

namespace cartographer {
namespace cloud {
namespace handlers {

DEFINE_HANDLER_SIGNATURE(
    GetCloudTrajectoryStateSignature, proto::GetCloudTrajectoryStateRequest,
    google::protobuf::Empty,
    "/cartographer.cloud.proto.MapBuilderService/GetCloudTrajectoryState")

class GetCloudTrajectoryStateHandler
    : public async_grpc::RpcHandler<GetCloudTrajectoryStateSignature> {
 public:
  void OnRequest(const proto::GetCloudTrajectoryStateRequest& request) override;
};

}  // namespace handlers
}  // namespace cloud
}  // namespace cartographer

#endif  // CARTOGRAPHER_CLOUD_INTERNAL_HANDLERS_GET_CLOUD_TRAJECTORY_STATE_HANDELR_H
