#include <iostream>
#include <map>
#include "gtest/gtest.h"
#include "jwt/jwt.hpp"

TEST (EncodeTest, StrEncodeHS2561)
{
  using namespace jwt::params;

  const char* expected_sign = 
   "eyJhbGciOiJIUzI1NiIsInR5cCI6IkpXVCJ9."
   "eyJpYXQiOjE1MTM4NjIzNzEsImlkIjoiYS1iLWMtZC1lLWYtMS0yLTMiLCJpc3MiOiJhcnVuLm11cmFsaWRoYXJhbiIsInN1YiI6ImFkbWluIn0."
   "jk7bRQKTLvs1RcuvMc2B_rt6WBYPoVPirYi_QRBPiuk";

  jwt::jwt_object obj{algorithm("hs256"), secret("secret")};

  obj.add_claim("iss", "arun.muralidharan")
     .add_claim("sub", "admin")
     .add_claim("id", "a-b-c-d-e-f-1-2-3")
     .add_claim("iat", 1513862371)
     ;

  std::cout << "Header: " << obj.header() << std::endl;
  std::cout << "Payload: "<< obj.payload() << std::endl;

  std::string enc_str = obj.signature();

  std::cout << "Signature: " << enc_str << std::endl;

  EXPECT_EQ (enc_str, expected_sign);
}

TEST (EncodeTest, StrEncodeHS2562)
{
  using namespace jwt::params;

  const char* expected_sign =
    "eyJhbGciOiJIUzI1NiIsInR5cCI6IkpXVCJ9."
    "eyJpYXQiOjE1MTM4NjIzNzEsImlkIjoiYS1iLWMtZC1lLWYtMS0yLTMiLCJpc3MiOiJhcnVuLm11cmFsaWRoYXJhbiIsInN1YiI6ImFkbWluIn0."
    "jk7bRQKTLvs1RcuvMc2B_rt6WBYPoVPirYi_QRBPiuk";

  jwt::jwt_object obj{algorithm("HS256"),
                      secret("secret"),
                      payload(
                          {
                            {"iss", "arun.muralidharan"},
                            {"sub", "admin"},
                            {"id", "a-b-c-d-e-f-1-2-3"}
                          })
                     };

  obj.add_claim("iat", 1513862371);

  std::string enc_str = obj.signature();
  EXPECT_EQ (enc_str, expected_sign);
}


TEST (EncodeTest, StrEncodeNONE)
{
  using namespace jwt::params;

  const char* expected_sign = 
    "eyJhbGciOiJOT05FIiwidHlwIjoiSldUIn0.eyJhdWQiOiJyaWZ0LmlvIiwiZXhwIjoxNTEzODYzMzcxLCJzdWIiOiJub3RoaW5nIG11Y2gifQ.";

  jwt::jwt_object obj{algorithm("none")};

  obj.add_claim("aud", "rift.io")
     .add_claim("exp", 1513863371)
     .add_claim("sub", "nothing much")
     ;

  std::cout << "Header: " << obj.header() << std::endl;
  std::cout << "Payload: " << obj.payload() << std::endl;

  std::string enc_str = obj.signature();

  EXPECT_EQ (enc_str, expected_sign);
}

TEST (EncodeTest, StrEncodeHS256WithKey)
{
  using namespace jwt::params;

  const char* expected_sign = 
    "eyJhbGciOiJIUzI1NiIsInR5cCI6IkpXVCJ9."
    "eyJhdWQiOiJyaWZ0LmlvIiwiZXhwIjoxNTEzODYzMzcxLCJzdWIiOiJub3RoaW5nIG11Y2gifQ."
    "W6t7mUX6ZJwOVTsVhHSKyBSwi0wnibobdsk456wSmJg";

  jwt::jwt_object obj{algorithm(jwt::algorithm::HS256),
                      secret("0123456789abcdefghijklmnopqrstuvwxyz"),
                      payload(
                          {
                            {"aud", "rift.io"},
                            {"sub", "nothing much"}
                          })
                     };
  obj.add_claim("exp", 1513863371);

  std::string enc_str = obj.signature();

  EXPECT_EQ (expected_sign, enc_str);
}

TEST (EncodeTest, StrEncodeHS384WithKey)
{

  using namespace jwt::params;

  const char* expected_sign = 
    "eyJhbGciOiJIUzM4NCIsInR5cCI6IkpXVCJ9."
    "eyJhdWQiOiJyaWZ0LmlvIiwiZXhwIjoxNTEzODYzMzcxLCJzdWIiOiJub3RoaW5nIG11Y2gifQ."
    "cGN4FZCe9Y2c1dA-jP71IXGnYbJRc4OaUTa5m7N7ybF5h6wBwxWQ-pdcxYchjDBL";

  jwt::jwt_object obj{algorithm(jwt::algorithm::HS384),
                      secret("0123456789abcdefghijklmnopqrstuvwxyz"),
                      payload(
                          {
                            {"aud", "rift.io"},
                            {"sub", "nothing much"}
                          })
                     };
  obj.add_claim("exp", 1513863371);

  std::string enc_str = obj.signature();

  EXPECT_EQ (expected_sign, enc_str);
}

TEST (EncodeTest, StrEncodeHS512WithKey)
{
  using namespace jwt::params;

  const char* expected_sign = 
    "eyJhbGciOiJIUzUxMiIsInR5cCI6IkpXVCJ9."
    "eyJhdWQiOiJyaWZ0LmlvIiwiZXhwIjoxNTEzODYzMzcxLCJzdWIiOiJub3RoaW5nIG11Y2gifQ."
    "vQ-1JSFN1kPjUI3URP6AFK5z8V7xLhyhw-76QWhQg9Xcy-IgrJ-bCTYLBjgaprrcEWwpSnBQnP3QnIxYK0HEaQ";

  jwt::string_view key = "00112233445566778899";

  std::map<jwt::string_view, jwt::string_view> p;
  p["aud"] = "rift.io";
  p["sub"] = "nothing much";

  jwt::jwt_object obj{algorithm(jwt::algorithm::HS512),
                      secret(key),
                      payload(std::move(p))
                     };
  obj.add_claim("exp", 1513863371);

  std::string enc_str = obj.signature();

  EXPECT_EQ (enc_str, expected_sign);
}

TEST (EncodeTest, StrEncodeChangeAlg)
{
  using namespace jwt::params;

  const char* expected_none_sign = 
    "eyJhbGciOiJOT05FIiwidHlwIjoiSldUIn0.eyJhdWQiOiJyaWZ0LmlvIiwiZXhwIjoxNTEzODYzMzcxLCJzdWIiOiJub3RoaW5nIG11Y2gifQ.";

  jwt::string_view key = "00112233445566778899";

  std::map<std::string, jwt::string_view> p;
  p["aud"] = "rift.io";
  p["sub"] = "nothing much";

  jwt::jwt_object obj{algorithm(jwt::algorithm::HS512),
                      secret(key),
                      payload(std::move(p))
                     };
  obj.add_claim("exp", 1513863371);

  obj.header().algo("none");
  std::string enc_str = obj.signature();

  EXPECT_EQ (expected_none_sign, enc_str);
}

TEST (EncodeTest, StrEncodeNoKey)
{
  using namespace jwt::params;

  jwt::jwt_object obj{algorithm(jwt::algorithm::HS512),
                      payload({{"iss", "arn-ml"}})
                      };

  std::error_code ec;
  std::string enc_str = obj.signature(ec);

  ASSERT_TRUE (ec);
  EXPECT_EQ (ec.value(), static_cast<int>(jwt::AlgorithmErrc::KeyNotFoundErr));
}

TEST (EncodeTest, StrEncodeNoneAlgWithKey)
{
  using namespace jwt::params;

  const jwt::string_view secret1 = "abcdefghijklmnopqrstuvwxyz";
  const jwt::string_view secret2 = "0123456789qwertybabe";

  jwt::jwt_object obj{algorithm("NONE"),
                      payload({{"iss", "arn-ml"}}),
                      secret(secret1)};

  std::error_code ec;
  std::string enc_str1 = obj.signature(ec);
  ASSERT_FALSE (ec);

  obj.secret(secret2);
  std::string enc_str2 = obj.signature(ec);
  ASSERT_FALSE (ec);

  EXPECT_EQ (enc_str1, enc_str2);
}

int main(int argc, char **argv) 
{
  ::testing::InitGoogleTest(&argc, argv);
  return RUN_ALL_TESTS();
}