// Only allowed header per problem statement
#include <vector>

// No 'using namespace std'; keep qualifiers explicit.

template <typename T>
class Expect {
 public:
  explicit Expect(const T& value) : value_(value), result_(true), negate_(false) {}

  // Equality: x == y
  Expect& toBe(const T& y) {
    applyCondition(value_ == y);
    return *this;
  }

  // Membership: exists z in y such that x == z
  Expect& toBeOneOf(const std::vector<T>& vec) {
    bool found = false;
    for (const auto& z : vec) {
      if (value_ == z) { found = true; break; }
    }
    applyCondition(found);
    return *this;
  }

  // x <= y, x >= y using only operator<
  Expect& le(const T& y) { applyCondition(!(y < value_)); return *this; }
  Expect& ge(const T& y) { applyCondition(!(value_ < y)); return *this; }

  // x < y, x > y
  Expect& lt(const T& y) { applyCondition(value_ < y); return *this; }
  Expect& gt(const T& y) { applyCondition(y < value_); return *this; }

  // Negate subsequent conditions
  Expect& Not() { negate_ = !negate_; return *this; }

  // Implicit conversion to bool for if conditions
  operator bool() const { return result_; }

 private:
  void applyCondition(bool cond) {
    if (negate_) cond = !cond;
    result_ = result_ && cond;
  }

  T value_;
  bool result_;
  bool negate_;
};

// Helper factory function
template <typename T>
Expect<T> expect(const T& x) { return Expect<T>(x); }

