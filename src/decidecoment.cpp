#include <decidecoment.hpp>
#include <eosio/system.hpp>

ACTION decidecoment::comment(name sender, name ballot_name, string comment) {
  require_auth(sender);

  // Init the _comment table
  comments_table _comments(get_self(), sender.value);
  auto it_comment = _comments.find( ballot_name.value );
  uint32_t date = eosio::current_time_point().sec_since_epoch();

  if(it_comment != _comments.end()) {
    _comments.modify(it_comment, get_self(), [&]( auto& row ) {
    row.comment = comment;
    row.date = date;
    });
  }

  else { 
    _comments.emplace(sender,[&]( auto& row ) {
    row.ballot_name = ballot_name;
    row.comment = comment;
    row.date = date;
    });
  }
  
}

ACTION decidecoment::erase(name sender, name ballot_name) {
  require_auth(sender);

  // Init the _comment table
  comments_table _comments(get_self(), sender.value);
  auto it_comment = _comments.find( ballot_name.value );
  check(it_comment != _comments.end(), "Can't find comment");

  _comments.erase(it_comment);

}