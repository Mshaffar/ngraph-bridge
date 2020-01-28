/*******************************************************************************
 * Copyright 2017-2019 Intel Corporation
 *
 * Licensed under the Apache License, Version 2.0 (the "License");
 * you may not use this file except in compliance with the License.
 * You may obtain a copy of the License at
 *
 *     http://www.apache.org/licenses/LICENSE-2.0
 *
 * Unless required by applicable law or agreed to in writing, software
 * distributed under the License is distributed on an "AS IS" BASIS,
 * WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 * See the License for the specific language governing permissions and
 * limitations under the License.
 *******************************************************************************/
#pragma once

#ifndef NGRAPH_TF_MARK_FOR_CLUSTERING_H_
#define NGRAPH_TF_MARK_FOR_CLUSTERING_H_

#include "tensorflow/core/graph/graph.h"

#include "ngraph/ngraph.hpp"

#include "ngraph_bridge/ngraph_encapsulate_clusters.h"

namespace tensorflow {

namespace ngraph_bridge {

Status MarkForClustering(Graph* graph, std::set<string> skip_these_nodes,
                         const string& current_backend,
                         const std::set<ShapeHintMap>& hints);
Status QueryBackendForSupport(Graph* graph,
                              ngraph::runtime::Backend* op_backend,
                              const string& current_backend,
                              const std::set<ShapeHintMap>& hints,
                              std::vector<Node*>& nodes_marked_for_clustering);
// remove marking, backend and static input nodes attributes
void ResetMarkForClustering(Graph* graph);
bool NodeIsMarkedForClustering(const Node* node);
void GetStaticInputs(const Node* node, std::vector<int32>* inputs);
bool InputIsStatic(const Node* node, int index);
Status GetNodeBackend(const Node* node, string* backend_name);
void SetNodeBackend(Node* node, const string& backend_name);

using SetAttributesFunction = std::function<Status(Node*)>;
const std::map<std::string, SetAttributesFunction>& GetAttributeSetters();

using TypeConstraintMap =
    std::map<std::string, std::map<std::string, gtl::ArraySlice<DataType>>>;
const TypeConstraintMap& GetTypeConstraintMap();

using ConfirmationFunction = std::function<Status(Node*, bool*)>;
const std::map<std::string, ConfirmationFunction>& GetConfirmationMap();

const std::map<std::string, std::set<std::shared_ptr<ngraph::Node>>>&
GetTFToNgOpMap();
}  // namespace ngraph_bridge
}  // namespace tensorflow

#endif  // NGRAPH_TF_MARK_FOR_CLUSTERING_H_
