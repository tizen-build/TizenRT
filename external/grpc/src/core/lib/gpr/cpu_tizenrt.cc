#include <grpc/support/port_platform.h>

#if defined(GPR_CPU_TIZENRT)

#include <errno.h>
#include <pthread.h>
#include <string.h>
#include <unistd.h>

#include <grpc/support/alloc.h>
#include <grpc/support/cpu.h>
#include <grpc/support/log.h>
#include <grpc/support/sync.h>
#include <grpc/support/useful.h>

static long ncpus = 0;

static pthread_key_t thread_id_key;

static void init_ncpus() {
    ncpus = 1;
}

unsigned gpr_cpu_num_cores(void) {
  static gpr_once once = GPR_ONCE_INIT;
  gpr_once_init(&once, init_ncpus);
  return (unsigned)ncpus;
}

static void delete_thread_id(void* value) {
  if (value) {
    gpr_free(value);
  }
}

static void init_thread_id_key(void) {
  pthread_key_create(&thread_id_key, delete_thread_id);
}

unsigned gpr_cpu_current_cpu(void) {
  /* NOTE: there's no way I know to return the actual cpu index portably...
     most code that's using this is using it to shard across work queues though,
     so here we use thread identity instead to achieve a similar though not
     identical effect */
  static gpr_once once = GPR_ONCE_INIT;
  gpr_once_init(&once, init_thread_id_key);

  unsigned int* thread_id =
      static_cast<unsigned int*>(pthread_getspecific(thread_id_key));
  if (thread_id == nullptr) {
    thread_id = static_cast<unsigned int*>(gpr_malloc(sizeof(unsigned int)));
    pthread_setspecific(thread_id_key, thread_id);
  }

  return (unsigned)GPR_HASH_POINTER(thread_id, gpr_cpu_num_cores());
}

#endif /* GPR_CPU_POSIX */
