#ifndef H_SORTEDUNTIL
#define H_SORTEDUNTIL

template <typename T>

T *IsSortedUntil(T *s, T *e) {
  if (s == e) {
    return e;
  }
  while (s != e) {
    s++;
    if (*s < *(s - 1)) {
      return s;
    }
  }
  return e;
}

#endif