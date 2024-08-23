#include <check.h>
#include <stdbool.h>
#include <stdio.h>

#include "../../../gui/cli/frontend.h"
#include "../backend.h"

START_TEST(test_1) {
  GameInfo_t *stats = get_Game_Info_t();
  //   init_game();
  start_game();
  move_figure(Left);
  move_figure(Right);
  rotate_figure();
  pause_game();
  pause_game();
  move_figure(Down);
  TerminatePushed();
  ck_assert_int_eq(stats->stop, 1);
  Quit();
}
END_TEST

START_TEST(test_2) {
  GameInfo_t *stats = get_Game_Info_t();
  start_game();
  move_figure(Left);
  move_figure(Right);
  UserAction_t action;
  int key = 's';
  parse_key(key, &action);
  key = KEY_LEFT;
  parse_key(key, &action);
  key = KEY_RIGHT;
  parse_key(key, &action);
  key = KEY_DOWN;
  parse_key(key, &action);
  key = 'r';
  parse_key(key, &action);
  userInput(Right, 1);
  userInput(Action, 1);
  userInput(Left, 1);
  userInput(Pause, 1);
  key = 's';
  parse_key(key, &action);
  key = 'n';
  parse_key(key, &action);
  key = 'y';
  parse_key(key, &action);
  userInput(Up, 1);
  userInput(Start, 1);
  rotate_figure();
  pause_game();
  pause_game();
  move_figure(Down);

  parse_key(key, &action);
  userInput(Terminate, 1);
  key = 'y';
  parse_key(key, &action);
  play_again();
  ck_assert_int_eq(stats->started, 1);
  deleteLines();
  updateCurrentState();
  getGravity(5);
  userInput(Terminate, 1);
  ck_assert_int_eq(stats->stop, 1);
  key = 'n';
  parse_key(key, &action);
}

Suite *back() {
  Suite *s;
  TCase *tc_core;

  s = suite_create("back func");
  tc_core = tcase_create("Core");

  tcase_add_test(tc_core, test_1);
  tcase_add_test(tc_core, test_2);
  suite_add_tcase(s, tc_core);

  return s;
}

int test_backend() {
  int no_failed = 0;

  Suite *s;
  SRunner *runner;

  s = back();
  runner = srunner_create(s);

  srunner_run_all(runner, CK_NORMAL);
  no_failed = srunner_ntests_failed(runner);
  srunner_free(runner);

  return no_failed;
}

int main() {
  int no_failed = 0;

  no_failed |= test_backend();

  return (no_failed == 0) ? EXIT_SUCCESS : EXIT_FAILURE;
}
