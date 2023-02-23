#include <iostream>
#include <memory>

#include "catch.hpp"

// 代表数据库中User表中的一条记录
class RecUser {
  int32_t uid;
  std::string uname;
};

// 代表数据库中Department表中一条记录
class RecDepartment {
  int32_t did;
  std::string dname;
};

// 1. 用户表操作抽象接口
class IUser {
public:
  virtual void insert(const RecUser *user) = 0;
  virtual RecUser *getUserRecord(int32_t id) = 0;
  virtual ~IUser() = default;
};

// 2.1 User表操作实现类：SQL Server
class SqlServerUser : public IUser {
public:
  void insert(const RecUser *user) override {
    std::cout << "Insert a user record into SQL Server table." << std::endl;
  }
  RecUser *getUserRecord(int32_t id) override {
    std::cout << "Get a record from SQL Server table." << std::endl;
    return nullptr;
  }
  ~SqlServerUser() override {
    std::cout << "dtor of SqlServerUser." << std::endl;
  }
};

// 2.2 User表操作实现类：access 表
class AccessUser : public IUser {
public:
  void insert(const RecUser *user) override {
    std::cout << "Insert a user record into access table." << std::endl;
  }
  RecUser *getUserRecord(int32_t id) override {
    std::cout << "Get a record from access table." << std::endl;
    return nullptr;
  }
  ~AccessUser() override {
    std::cout << "dtor of AccessUser. " << std::endl;
  }
};

// 3. 抽象工厂类
class IFactory {
public:
  virtual IUser *createUser() = 0;
};

// 4.1 SQL Server 具体工厂类
class SqlFactory : public IFactory {
public:
  IUser *createUser() override {
    return new SqlServerUser;
  }
};

// 4.2 access 具体工厂类
class AccessFactory : public IFactory {
public:
  IUser *createUser() override {
    return new AccessUser;
  }
};

TEST_CASE("design mode: abstract factory") {
  RecUser user_rec;

  // 创建类型1实例：SQL表操作
  std::shared_ptr<IFactory> factory(new SqlFactory);
  std::shared_ptr<IUser> user_table(factory->createUser());
  user_table->insert(&user_rec);
  user_table->getUserRecord(1);

  // 创建类型2实例：access表操作
  factory.reset(new AccessFactory);
  user_table.reset(factory->createUser());
  user_table->insert(&user_rec);
  user_table->getUserRecord(1);
}