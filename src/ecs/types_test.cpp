#include <ecs/types.h>
#include <iostream>
#include <type_traits>

/**
 * @brief 编译验证程序
 *
 * 验证 sop::ecs::types 模块的所有类型可以被正确编译和使用。
 * 本程序不执行任何实际逻辑，仅用于编译验证。
 */
int main() {
    // 测试 EntityId（强类型枚举）
    sop::ecs::EntityId entity_id = sop::ecs::make_entity_id(1);
    sop::ecs::EntityId invalid_entity_id = sop::ecs::INVALID_ENTITY_ID;
    sop::ecs::EntityId entity_id2 = sop::ecs::EntityId(2);
    uint64_t entity_id_value = sop::ecs::to_underlying(entity_id);
    bool entity_equal = (entity_id == entity_id2);
    bool entity_not_equal = (entity_id != entity_id2);
    (void)entity_id;
    (void)invalid_entity_id;
    (void)entity_id2;
    (void)entity_id_value;
    (void)entity_equal;
    (void)entity_not_equal;

    // 测试 ComponentTypeId（强类型枚举）
    sop::ecs::ComponentTypeId component_type_id = sop::ecs::make_component_type_id(1);
    sop::ecs::ComponentTypeId invalid_component_type_id = sop::ecs::INVALID_COMPONENT_TYPE_ID;
    sop::ecs::ComponentTypeId component_type_id2 = sop::ecs::ComponentTypeId(2);
    uint32_t component_type_id_value = sop::ecs::to_underlying(component_type_id);
    bool component_equal = (component_type_id == component_type_id2);
    bool component_not_equal = (component_type_id != component_type_id2);
    (void)component_type_id;
    (void)invalid_component_type_id;
    (void)component_type_id2;
    (void)component_type_id_value;
    (void)component_equal;
    (void)component_not_equal;

    // 测试 Phase
    sop::ecs::Phase phase = sop::ecs::Phase::Input;
    (void)phase;

    // 测试 SystemId（强类型枚举）
    sop::ecs::SystemId system_id = sop::ecs::make_system_id(1);
    sop::ecs::SystemId invalid_system_id = sop::ecs::INVALID_SYSTEM_ID;
    sop::ecs::SystemId system_id2 = sop::ecs::SystemId(2);
    uint32_t system_id_value = sop::ecs::to_underlying(system_id);
    bool system_equal = (system_id == system_id2);
    bool system_not_equal = (system_id != system_id2);
    (void)system_id;
    (void)invalid_system_id;
    (void)system_id2;
    (void)system_id_value;
    (void)system_equal;
    (void)system_not_equal;

    // 测试 SubscriptionId（强类型枚举）
    sop::ecs::SubscriptionId subscription_id = sop::ecs::make_subscription_id(1);
    sop::ecs::SubscriptionId invalid_subscription_id = sop::ecs::INVALID_SUBSCRIPTION_ID;
    sop::ecs::SubscriptionId subscription_id2 = sop::ecs::SubscriptionId(2);
    uint32_t subscription_id_value = sop::ecs::to_underlying(subscription_id);
    bool subscription_equal = (subscription_id == subscription_id2);
    bool subscription_not_equal = (subscription_id != subscription_id2);
    (void)subscription_id;
    (void)invalid_subscription_id;
    (void)subscription_id2;
    (void)subscription_id_value;
    (void)subscription_equal;
    (void)subscription_not_equal;

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

    // 验证 to_underlying 的类型推导正确性
    // EntityId 应该返回 uint64_t
    static_assert(std::is_same_v<decltype(sop::ecs::to_underlying(entity_id)), uint64_t>,
                  "EntityId to_underlying should return uint64_t");

    // ComponentTypeId 应该返回 uint32_t
    static_assert(std::is_same_v<decltype(sop::ecs::to_underlying(component_type_id)), uint32_t>,
                  "ComponentTypeId to_underlying should return uint32_t");

    // SystemId 应该返回 uint32_t
    static_assert(std::is_same_v<decltype(sop::ecs::to_underlying(system_id)), uint32_t>,
                  "SystemId to_underlying should return uint32_t");

    // SubscriptionId 应该返回 uint32_t
    static_assert(std::is_same_v<decltype(sop::ecs::to_underlying(subscription_id)), uint32_t>,
                  "SubscriptionId to_underlying should return uint32_t");

    // Phase 应该返回 uint8_t
    static_assert(std::is_same_v<decltype(sop::ecs::to_underlying(phase)), uint8_t>,
                  "Phase to_underlying should return uint8_t");

    // Result 应该返回 uint8_t
    static_assert(std::is_same_v<decltype(sop::ecs::to_underlying(result)), uint8_t>,
                  "Result to_underlying should return uint8_t");

    std::cout << "Types module compilation test passed." << std::endl;
    std::cout << "Type deduction verification passed." << std::endl;

    return 0;
}