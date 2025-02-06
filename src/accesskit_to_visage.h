//
// Created by Paul Walker on 2/5/25.
//

#ifndef ACCESSIKIT_TO_VISAGE_H
#define ACCESSIKIT_TO_VISAGE_H

#include <visage_ui/frame.h>
#include "config.h"

#if HAS_ACCESSKIT
#include "accesskit.h"

namespace baconpaul::visage_learn
{

struct ProvidesAK
{
  virtual ~ProvidesAK() = default;
  virtual std::pair<accesskit_node *, uint32_t> getAKNode() = 0;
};

struct ak_window_state
{
  accesskit_macos_subclassing_adapter *adapter{nullptr};
  visage::Frame *frame{nullptr};

  ~ak_window_state()
  {
    if (adapter)
      accesskit_macos_subclassing_adapter_free(adapter);
  }
  void setup(void *w)
  {
    if (adapter)
      return;
    adapter = accesskit_macos_subclassing_adapter_new(w, activate_cb, this, action_cb, this);
    VLLOG("AccessKit adapter set up " << adapter);
  }

  std::vector<std::pair<accesskit_node *, uint32_t>> collectTree(visage::Frame &frame)
  {
    std::vector<std::pair<accesskit_node *, uint32_t>> result;
    for (auto *c : frame.children())
    {
      if (dynamic_cast<ProvidesAK *>(c))
      {
        auto *p = dynamic_cast<ProvidesAK *>(c);
        auto cres  = p->getAKNode();
        result.push_back(cres);
      }
      auto kidTree = collectTree(*c);
      if (!kidTree.empty())
        result.insert(result.end(), kidTree.begin(), kidTree.end());
    }
    return result;
  }

  void setFrame(visage::Frame *frame) { this->frame = frame;}
  void doAction(struct accesskit_action_request *request)
  {
    VLLOG("Accessible action " << adapter);
    accesskit_action_request_free(request);
  }

  accesskit_tree_update* doActivation()
  {
    VLLOG("doActivation");
    auto kids = collectTree(*frame);
    VLLOG("Collected " << kids.size() << " children");
    accesskit_node *node = accesskit_node_new(ACCESSKIT_ROLE_WINDOW);

    for (auto &[p,id] : kids)
      accesskit_node_push_child(node, id);

    accesskit_tree_update *result = accesskit_tree_update_with_capacity_and_focus(
      kids.size(), kids[0].second);
    static constexpr uint32_t WINDOW_ID = 3;
    accesskit_tree *tree = accesskit_tree_new(WINDOW_ID);
    accesskit_tree_set_app_name(tree, "Visage App");
    accesskit_tree_update_set_tree(result, tree);
    accesskit_tree_update_push_node(result, WINDOW_ID, node);
    for (auto &[p,id] : kids)
      accesskit_tree_update_push_node(result, id, p);

    return result;
  }
  static accesskit_tree_update* activate_cb(void *userdata)
  {
    VLLOG("Activate callback");
    auto that = (ak_window_state *)userdata;
    return that->doActivation();
  }
  static void action_cb( struct accesskit_action_request *request, void *userdata)
  {
    VLLOG("Action callback");
    auto that = (ak_window_state *)userdata;
    that->doAction(request);
  }
};

} // namespace baconpaul::visage_learn
#else


namespace baconpaul::visage_learn
{
using accesskit_node = void;
struct ProvidesAK
{
  virtual ~ProvidesAK() = default;
  virtual std::pair<accesskit_node *, uint32_t> getAKNode() = 0;
};
struct ak_window_state
{
  void setup(void* ){}
  void setFrame(void *) {}
};
}
#endif

#endif // ACCESSIKIT_TO_VISAGE_H
