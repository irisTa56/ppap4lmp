import traceback
import numpy as np

def check_error_msg(testcase, expected_msg, callback, *args, **kwargs):
  """
  @param testcase
    Subclass of unittest.TestCase.
  @param expected_msg
    Exptected error message.
  @param callback
    A function supposed to raise the error.
  @param *args
    Arguments to be passed to `callback`.
  @param **kwargs
    keyword arguments to be passed to `callback`.

  @return None.
  """
  try:
    if args:
      callback(*args)
    else:
      callback()
  except SystemError:
    msg = traceback.format_exc()
    testcase.assertEqual(msg.split("\n")[0], expected_msg)

def generate_random_unit_vector():
  """
  @return Unit vector with random direction.
  """
  while True:
    x = np.random.randn(3)  # standard normal distribution
    r = np.linalg.norm(x)
    if r != 0.:
      return x/r

def rotate_vector(v, n, deg):
  """
  @param v
    Vector to be rotated. This vector rotates around its starting point.
  @param n
    Direction vector representing rotation axis.
  @param deg
    Rotation angle in degree.

  @return Rotated vector `v`.
  """
  cos = np.cos(deg*np.pi/360)
  sin = np.sin(deg*np.pi/360)

  unit_n = np.array(n) / np.linalg.norm(n)  # normalizing

  q1 = [unit_n[0]*sin, unit_n[1]*sin, unit_n[2]*sin, cos]
  q2 = list(v) + [0.0]

  return _q_mult(_q_mult(q1, q2), _q_conjugate(q1))[:3]

def _q_mult(q1, q2):

  x1, y1, z1, w1 = q1
  x2, y2, z2, w2 = q2

  w = w1 * w2 - x1 * x2 - y1 * y2 - z1 * z2
  x = w1 * x2 + x1 * w2 + y1 * z2 - z1 * y2
  y = w1 * y2 + y1 * w2 + z1 * x2 - x1 * z2
  z = w1 * z2 + z1 * w2 + x1 * y2 - y1 * x2

  return x, y, z ,w

def _q_conjugate(q):

  x, y, z, w = q

  return -x, -y, -z, w