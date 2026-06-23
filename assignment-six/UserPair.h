
// class UserPair: holds user ID and password
// as described in the assignment, it has a string id and password, and defines
// operator< for AVL tree ordering by ID.

class UserPair {
public:
  string id;
  string password;

  UserPair() : id(""), password("") {}
  UserPair(const string &i, const string &p) : id(i), password(p) {}

  bool operator<(const UserPair &o) const { return id < o.id; }
  bool operator>(const UserPair &o) const { return id > o.id; }
  bool operator==(const UserPair &o) const { return id == o.id; }
};
