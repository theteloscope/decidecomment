#include <eosio/eosio.hpp>

using namespace std;
using namespace eosio;

CONTRACT decidecoment : public contract {
  public:
    using contract::contract;

    ACTION comment(name sender, name ballot_name, string comment);
    ACTION erase(name sender, name ballot_name);

  private:
    TABLE comments {
      name ballot_name;
      string  comment;
      uint32_t date;
      auto primary_key() const { return ballot_name.value; }
    };
    typedef multi_index<name("comments"), comments> comments_table;
};

EOSIO_DISPATCH(decidecoment, (comment)(erase))