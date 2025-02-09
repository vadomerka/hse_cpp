#include <unistd.h>
#include <stdio.h>
#include <stdint.h>
#include <stdlib.h>


uint64_t phib(uint64_t n) {
  uint64_t f = 1;
  uint64_t s = 1;
  for (uint64_t i = 1; i < n; i++) {
    uint64_t tmp = s;
    s = f + s;
    f = tmp;
    if (s > UINT64_MAX - f) {
      printf("Phibonacchi stopped at: %ld\t", i);
      return 0;
    }
  }
  return s;
}

uint64_t fact(uint64_t n) {
  uint64_t a = 1;
  // uint64_t p = a;
  for (uint64_t i = 2; i <= n; i++) {
    // p = a;
    a *= i;
    if (a > UINT64_MAX / i) {
      printf("Factorial stopped at: %ld\t", i);
      return 0;
    }
  }
  return a;
}

int main(int argc, char* argv[]) {
  if (argc != 2) {
    printf("Wrong arguments!\n");
    return 0;
  }
  uint64_t num = std::strtoull(argv[1], NULL, 10);

  // printf("id = %d, my gid = %d\n", (int)uid, (int)gid);
  pid_t chpd = fork();
  // printf("id = %d, my gid = %d\n", (int)uid, (int)gid);
  // printf("chpd: %d", chpd);
  // int num = 6;
  if (chpd == -1) {
    printf("error\n");
    return 0;
  }
  if (chpd == 0) {
    // printf("child spotted\n");
    // fact
    printf("Child calculates factorial: pid = %d, ppid = %d\n", getpid(), getppid());
    uint64_t res = fact(num);
    if (res == 0) {
      printf("Overflow!\n");
    } else {
      printf("Factorial: %ld\n", res);
    }
    exit(0);
  } 
  chpd = fork();
  if (chpd == -1) {
    printf("error\n");
    return 0;
  }
  if (chpd == 0) {
    printf("Parent outputs info of directory: pid = %d, ppid = %d\n", getpid(), getppid());
    system("ls -l");
    exit(0);
  }
  // printf("parent spotted\n");
  // phib
  printf("Parent calculates phibonacchi: pid = %d, ppid = %d\n", getpid(), getppid());
  uint64_t res = phib(num);
  if (!res) {
    printf("Overflow!\n");
  } else {
    printf("Phibonacchi: %ld\n", res);
  }
  
  return 0;
}
