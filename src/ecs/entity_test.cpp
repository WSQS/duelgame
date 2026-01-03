#include <ecs/entity.h>
#include <iostream>

/**
 * @brief Entity 模块验证程序
 *
 * 验证 sop::ecs::Entity 的所有接口和行为。
 */
int main() {
    std::cout << "=== Entity Module Test ===" << std::endl;

    // 测试 1: 默认构造函数（无效实体）
    sop::ecs::Entity invalid_entity;
    if (!invalid_entity.is_valid()) {
        std::cout << "[PASS] Default entity is invalid" << std::endl;
    } else {
        std::cout << "[FAIL] Default entity should be invalid" << std::endl;
        return 1;
    }

    // 测试 2: 无效实体的 ID
    if (invalid_entity.id() == sop::ecs::INVALID_ENTITY_ID) {
        std::cout << "[PASS] Invalid entity has INVALID_ENTITY_ID" << std::endl;
    } else {
        std::cout << "[FAIL] Invalid entity should have INVALID_ENTITY_ID" << std::endl;
        return 1;
    }

    // 测试 3: 有效实体构造
    sop::ecs::Entity valid_entity(sop::ecs::make_entity_id(1));
    if (valid_entity.is_valid()) {
        std::cout << "[PASS] Valid entity is valid" << std::endl;
    } else {
        std::cout << "[FAIL] Valid entity should be valid" << std::endl;
        return 1;
    }

    // 测试 4: 有效实体的 ID
    if (valid_entity.id() == sop::ecs::make_entity_id(1)) {
        std::cout << "[PASS] Valid entity has correct ID" << std::endl;
    } else {
        std::cout << "[FAIL] Valid entity should have correct ID" << std::endl;
        return 1;
    }

    // 测试 5: 相等比较（相同 ID）
    sop::ecs::Entity entity1(sop::ecs::make_entity_id(1));
    sop::ecs::Entity entity2(sop::ecs::make_entity_id(1));
    if (entity1 == entity2) {
        std::cout << "[PASS] Entities with same ID are equal" << std::endl;
    } else {
        std::cout << "[FAIL] Entities with same ID should be equal" << std::endl;
        return 1;
    }

    // 测试 6: 不等比较（不同 ID）
    sop::ecs::Entity entity3(sop::ecs::make_entity_id(1));
    sop::ecs::Entity entity4(sop::ecs::make_entity_id(2));
    if (entity3 != entity4) {
        std::cout << "[PASS] Entities with different IDs are not equal" << std::endl;
    } else {
        std::cout << "[FAIL] Entities with different IDs should not be equal" << std::endl;
        return 1;
    }

    // 测试 7: 不等比较（相同 ID）
    if (!(entity1 != entity2)) {
        std::cout << "[PASS] Entities with same ID are not not-equal" << std::endl;
    } else {
        std::cout << "[FAIL] Entities with same ID should not be not-equal" << std::endl;
        return 1;
    }

    // 测试 8: 相等比较（不同 ID）
    if (!(entity3 == entity4)) {
        std::cout << "[PASS] Entities with different IDs are not equal" << std::endl;
    } else {
        std::cout << "[FAIL] Entities with different IDs should not be equal" << std::endl;
        return 1;
    }

    // 测试 9: 无效实体的相等比较
    sop::ecs::Entity invalid1;
    sop::ecs::Entity invalid2;
    if (invalid1 == invalid2) {
        std::cout << "[PASS] Invalid entities are equal" << std::endl;
    } else {
        std::cout << "[FAIL] Invalid entities should be equal" << std::endl;
        return 1;
    }

    // 测试 10: 无效实体与有效实体的不等比较
    if (invalid_entity != valid_entity) {
        std::cout << "[PASS] Invalid and valid entities are not equal" << std::endl;
    } else {
        std::cout << "[FAIL] Invalid and valid entities should not be equal" << std::endl;
        return 1;
    }

    std::cout << "=== All Entity Module Tests Passed ===" << std::endl;

    return 0;
}