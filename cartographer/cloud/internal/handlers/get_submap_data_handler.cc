/*
 * Copyright 2018 The Cartographer Authors
 *
 * Licensed under the Apache License, Version 2.0 (the "License");
 * you may not use this file except in compliance with the License.
 * You may obtain a copy of the License at
 *
 *      http://www.apache.org/licenses/LICENSE-2.0
 *
 * Unless required by applicable law or agreed to in writing, software
 * distributed under the License is distributed on an "AS IS" BASIS,
 * WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 * See the License for the specific language governing permissions and
 * limitations under the License.
 */

#include "cartographer/cloud/internal/handlers/get_submap_data_handler.h"

#include "async_grpc/rpc_handler.h"
#include "cartographer/cloud/internal/map_builder_context_interface.h"
#include "cartographer/cloud/proto/map_builder_service.pb.h"
#include "cartographer/common/make_unique.h"
#include "cartographer/transform/transform.h"
#include "google/protobuf/empty.pb.h"

namespace cartographer
{
namespace cloud
{
namespace handlers
{

void GetSubmapDataHandler::OnRequest(const proto::GetSubmapDataRequest &request)
{
    auto response = common::make_unique<proto::GetSubmapDataResponse>();
    auto submapDataMap = GetContext<MapBuilderContextInterface>()
                             ->map_builder()
                             .pose_graph()
                             ->GetAllSubmapData();
    mapping::SubmapId submap_id = { request.submap_id().trajectory_id(),
                        request.submap_id().submap_index() };
    if (submapDataMap.Contains(submap_id))
    {
        auto *actual_response = response->mutable_submap_data_query_response();
        auto data = submapDataMap.at(submap_id);
        data.submap->ToProto(actual_response->mutable_submap(), true);
        *actual_response->mutable_pose() = transform::ToProto(data.pose);
        response->set_error_msg("");
    }
    else
    {
        response->set_error_msg("Not found.");
    }
    Send(std::move(response));
}

} // namespace handlers
} // namespace cloud
} // namespace cartographer