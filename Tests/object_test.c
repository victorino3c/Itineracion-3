#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "test.h"
#include "../object.h"
#include "object_test.h"

#define MAX_TESTS 19

/**
 * @brief Main function for Object unit tests.
 *
 * You may execute ALL or a SINGLE test
 *   1.- No parameter -> ALL test are executed
 *   2.- A number means a particular test (the one identified by that number)
 *       is executed
 */
int main(int argc, char **argv)
{

  int test = 0;
  int all = 1, i;

  if (argc < 2)
  {
    printf("Running all test for module Object:\n");
  }
  else
  {
    test = atoi(argv[1]);
    all = 0;
    printf("Running test %d:\t", test);
    if (test < 1 && test > MAX_TESTS)
    {
      printf("Error: unknown test %d\t", test);
      exit(EXIT_SUCCESS);
    }
  }

  i = 1;
  if (all || test == i) test1_obj_create();
  i++;
  if (all || test == i) test2_obj_create();
  i++;

  if (all || test == i) test1_obj_destroy();
  i++;
  if (all || test == i) test2_obj_destroy();
  i++;

  if (all || test == i) test1_obj_test_id();
  i++;
  if (all || test == i) test2_obj_test_id();
  i++;

  if (all || test == i) test1_obj_get_id();
  i++;
  if (all || test == i) test2_obj_get_id();
  i++;

  if (all || test == i) test1_obj_set_name();
  i++;
  if (all || test == i) test2_obj_set_name();
  i++;
  if (all || test == i) test3_obj_set_name();
  i++;

  if (all || test == i) test1_obj_get_name();
  i++;
  if (all || test == i) test2_obj_get_name();
  i++;

  if (all || test == i) test1_obj_set_location();
  i++;
  if (all || test == i) test2_obj_set_location();
  i++;
  if (all || test == i) test3_obj_set_location();
  i++;
  
  if (all || test == i) test1_obj_get_location();
  i++;
  if (all || test == i) test2_obj_get_location();
  i++;
  
  PRINT_PASSED_PERCENTAGE;

  return 0;
}
/* obj_create */
void test1_obj_create()
{
  int result;
  Object *obj = NULL;
  Id obj_id = FD_ID_OBJ*10 + 1;
  obj = obj_create(obj_id);
  result = obj != NULL;
  PRINT_TEST_RESULT(result);
  obj_destroy(obj);
}
void test2_obj_create()
{
  Object *obj = NULL;
  Id obj_id = FD_ID_OBJ*10 + 1;
  obj = obj_create(obj_id);
  PRINT_TEST_RESULT(obj_get_id(obj) == obj_id);
  obj_destroy(obj);
}

/* obj_destroy*/
void test1_obj_destroy()
{
  Object *obj = NULL;
  Id obj_id = FD_ID_OBJ*10 + 1;
  obj = obj_create(obj_id);
  PRINT_TEST_RESULT(obj_destroy(obj) == OK);
}
void test2_obj_destroy()
{
  Object *obj = NULL;
  PRINT_TEST_RESULT(obj_destroy(obj) == ERROR);
}

/* obj_test_id() */
void test1_obj_test_id()
{
    Id obj_id = FD_ID_OBJ*10 + 1;
    PRINT_TEST_RESULT(obj_test_id(obj_id) == OK);
}
void test2_obj_test_id()
{
    Id not_obj_id = FD_ID_PLAYER*10 + 1;
    PRINT_TEST_RESULT(obj_test_id(not_obj_id) == ERROR);
}

/*  obj_get_id*/
void test1_obj_get_id()
{
  Object *obj = NULL;
  Id obj_id = FD_ID_OBJ*10 + 1;
  obj = obj_create(obj_id);
  PRINT_TEST_RESULT(obj_get_id(obj) == obj_id);
  obj_destroy(obj);
}
void test2_obj_get_id()
{
  Object *obj = NULL;
  PRINT_TEST_RESULT(obj_get_id(obj) == NO_ID);
}

/* obj_set_name*/
void test1_obj_set_name()
{
  Object *obj;
  Id obj_id = FD_ID_OBJ*10 + 1;
  obj = obj_create(obj_id);
  PRINT_TEST_RESULT(obj_set_name(obj, "hola") == OK);
  obj_destroy(obj);
}
void test2_obj_set_name()
{
  Object *obj = NULL;
  PRINT_TEST_RESULT(obj_set_name(obj, "hola") == ERROR);
}
void test3_obj_set_name()
{
  Object *obj;
  Id obj_id = FD_ID_OBJ*10 + 1;
  obj = obj_create(obj_id);
  PRINT_TEST_RESULT(obj_set_name(obj, NULL) == ERROR);
  obj_destroy(obj);
}

/* obj_get_name */
void test1_obj_get_name()
{
  Object *obj = NULL;
  obj = obj_create(1);
  obj_set_name(obj, "adios");
  PRINT_TEST_RESULT(strcmp(obj_get_name(obj), "adios") == 0);
  obj_destroy(obj);
}
void test2_obj_get_name()
{
  Object *obj = NULL;
  PRINT_TEST_RESULT(obj_get_name(obj) == NULL);
}

/* obj_set_location */
void test1_obj_set_location()
{
  Object *obj = NULL;
  Id obj_id = FD_ID_OBJ*10 + 1;
  Id space_id = FD_ID_SPACE*10 + 1;
  obj = obj_create(obj_id);
  PRINT_TEST_RESULT(obj_set_location(obj, space_id) == OK);
  obj_destroy(obj);
}
void test2_obj_set_location()
{
  Object *obj = NULL;
  Id space_id = FD_ID_SPACE*10 + 1;
  PRINT_TEST_RESULT(obj_set_location(obj, space_id) == ERROR);
}
void test3_obj_set_location()
{
  Object *obj = NULL;
  Id obj_id = FD_ID_OBJ*10 + 1;
  obj = obj_create(obj_id);
  PRINT_TEST_RESULT(obj_set_location(obj, NO_ID) == OK);
  obj_destroy(obj);
}

/* obj_get_location */
void test1_obj_get_location()
{
  Object *obj = NULL;
  Id obj_id = FD_ID_OBJ*10 + 1;
  Id space_id = FD_ID_SPACE*10 + 1;
  obj = obj_create(obj_id);
  obj_set_location(obj, space_id);
  PRINT_TEST_RESULT(obj_get_location(obj) == space_id);
  obj_destroy(obj);
}
void test2_obj_get_location()
{
  Object *obj = NULL;
  PRINT_TEST_RESULT(obj_get_location(obj) == NO_ID);
}

