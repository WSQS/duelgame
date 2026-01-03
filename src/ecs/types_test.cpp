#include <ecs/types.h>
#include <iostream>

/**
 * @brief 编译验证程序
 *
 * 验证 sop::ecs::types 模块的所有类型可以被正确编译和使用。
 * 本程序不执行任何实际逻辑，仅用于编译验证。
 */
int main() {
    // 测试 EntityId
    sop::ecs::EntityId entity_id = 1;
    sop::ecs::EntityId invalid_entity_id = sop::ecs::INVALID_ENTITY_ID;
    (void)entity_id;
    (void)invalid_entity_id;

    // 测试 ComponentTypeId
    sop::ecs::ComponentTypeId component_type_id = 1;
    sop::ecs::ComponentTypeId invalid_component_type_id = sop::ecs::INVALID_COMPONENT_TYPE_ID;
    (void)component_type_id;
    (void)invalid_component_type_id;

    // 测试 Phase
    sop::ecs::Phase phase = sop::ecs::Phase::Input;
    (void)phase;

    // 测试 SystemId
    sop::ecs::SystemId system_id = 1;
    sop::ecs::SystemId invalid_system_id = sop::ecs::INVALID_SYSTEM_ID;
    (void)system_id;
    (void)invalid_system_id;

    // 测试 SubscriptionId
    sop::ecs::SubscriptionId subscription_id = 1;
    sop::ecs::SubscriptionId invalid_subscription_id = sop::ecs::INVALID_SUBSCRIPTION_ID;
    (void)subscription_id;
    (void)invalid_subscription_id;

    // 测试 Result
    sop::ecs::Result result = sop::ecs::Result::Success;
    (void)result;

    // 测试 Error
    sop::ecs::Error error(sop::ecs::Result::Success, "Test error");
    sop::ecs::Error error2(sop::ecs::Result::InvalidEntity, "Invalid entity");
    bool is_success = error.is_success();
    bool are_equal = (error == error2);
    bool are_not_equal = (error != error2);
    (void)is_success;
    (void)are_equal;
    (void)are_not_equal;

    std::cout << "Types module compilation test passed." << std::endl;

    return 0;
}