import traceback

def check_error_msg(testcase, expected_msg, callback, *args):

  try:
    if args:
      callback(*args)
    else:
      callback()
  except SystemError:
    msg = traceback.format_exc()
    testcase.assertEqual(msg.split("\n")[0], expected_msg)