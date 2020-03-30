#!/usr/bin/env python
#
# Python-bindings store type test script
#
# Copyright (C) 2011-2020, Joachim Metz <joachim.metz@gmail.com>
#
# Refer to AUTHORS for acknowledgements.
#
# This program is free software: you can redistribute it and/or modify
# it under the terms of the GNU Lesser General Public License as published by
# the Free Software Foundation, either version 3 of the License, or
# (at your option) any later version.
#
# This program is distributed in the hope that it will be useful,
# but WITHOUT ANY WARRANTY; without even the implied warranty of
# MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
# GNU General Public License for more details.
#
# You should have received a copy of the GNU Lesser General Public License
# along with this program.  If not, see <https://www.gnu.org/licenses/>.

import argparse
import os
import sys
import unittest

import pyvshadow


class StoreTypeTests(unittest.TestCase):
  """Tests the store type."""

  def test_read_buffer(self):
    """Tests the read_buffer function."""
    if not unittest.source or unittest.offset != 0:
      raise unittest.SkipTest("missing source")

    vshadow_volume = pyvshadow.volume()

    vshadow_volume.open(unittest.source)

    if vshadow_volume.number_of_stores > 0:
      vshadow_store = vshadow_volume.get_store(
          vshadow_volume.number_of_stores - 1)
      self.assertIsNotNone(vshadow_store)

      volume_size = vshadow_store.get_size()

      # Test normal read.
      data = vshadow_store.read_buffer(size=4096)

      self.assertIsNotNone(data)
      self.assertEqual(len(data), min(volume_size, 4096))

      if volume_size < 4096:
        data = vshadow_store.read_buffer()

        self.assertIsNotNone(data)
        self.assertEqual(len(data), volume_size)

      # Test read beyond volume size.
      if volume_size > 16:
        vshadow_store.seek_offset(-16, os.SEEK_END)

        data = vshadow_store.read_buffer(size=4096)

        self.assertIsNotNone(data)
        self.assertEqual(len(data), 16)

      with self.assertRaises(ValueError):
        vshadow_store.read_buffer(size=-1)

    vshadow_volume.close()

  def test_read_buffer_file_object(self):
    """Tests the read_buffer function on a file-like object."""
    if not unittest.source or unittest.offset != 0:
      raise unittest.SkipTest("missing source")

    vshadow_volume = pyvshadow.volume()

    vshadow_volume.open(unittest.source)

    if vshadow_volume.number_of_stores > 0:
      vshadow_store = vshadow_volume.get_store(
          vshadow_volume.number_of_stores - 1)
      self.assertIsNotNone(vshadow_store)

      volume_size = vshadow_store.get_size()

      # Test normal read.
      data = vshadow_store.read_buffer(size=4096)

      self.assertIsNotNone(data)
      self.assertEqual(len(data), min(volume_size, 4096))

    vshadow_volume.close()

  def test_read_buffer_at_offset(self):
    """Tests the read_buffer_at_offset function."""
    if not unittest.source or unittest.offset != 0:
      raise unittest.SkipTest("missing source")

    vshadow_volume = pyvshadow.volume()

    vshadow_volume.open(unittest.source)

    if vshadow_volume.number_of_stores > 0:
      vshadow_store = vshadow_volume.get_store(
          vshadow_volume.number_of_stores - 1)
      self.assertIsNotNone(vshadow_store)

      volume_size = vshadow_store.get_size()

      # Test normal read.
      data = vshadow_store.read_buffer_at_offset(4096, 0)

      self.assertIsNotNone(data)
      self.assertEqual(len(data), min(volume_size, 4096))

      # Test read beyond volume size.
      if volume_size > 16:
        data = vshadow_store.read_buffer_at_offset(4096, volume_size - 16)

        self.assertIsNotNone(data)
        self.assertEqual(len(data), 16)

      with self.assertRaises(ValueError):
        vshadow_store.read_buffer_at_offset(-1, 0)

      with self.assertRaises(ValueError):
        vshadow_store.read_buffer_at_offset(4096, -1)

    vshadow_volume.close()

  def test_seek_offset(self):
    """Tests the seek_offset function."""
    if not unittest.source or unittest.offset != 0:
      raise unittest.SkipTest("missing source")

    vshadow_volume = pyvshadow.volume()

    vshadow_volume.open(unittest.source)

    if vshadow_volume.number_of_stores > 0:
      vshadow_store = vshadow_volume.get_store(
          vshadow_volume.number_of_stores - 1)
      self.assertIsNotNone(vshadow_store)

      volume_size = vshadow_store.get_size()

      vshadow_store.seek_offset(16, os.SEEK_SET)

      offset = vshadow_store.get_offset()
      self.assertEqual(offset, 16)

      vshadow_store.seek_offset(16, os.SEEK_CUR)

      offset = vshadow_store.get_offset()
      self.assertEqual(offset, 32)

      vshadow_store.seek_offset(-16, os.SEEK_CUR)

      offset = vshadow_store.get_offset()
      self.assertEqual(offset, 16)

      vshadow_store.seek_offset(-16, os.SEEK_END)

      offset = vshadow_store.get_offset()
      self.assertEqual(offset, volume_size - 16)

      vshadow_store.seek_offset(16, os.SEEK_END)

      offset = vshadow_store.get_offset()
      self.assertEqual(offset, volume_size + 16)

      # TODO: change IOError into ValueError
      with self.assertRaises(IOError):
        vshadow_store.seek_offset(-1, os.SEEK_SET)

      # TODO: change IOError into ValueError
      with self.assertRaises(IOError):
        vshadow_store.seek_offset(-32 - volume_size, os.SEEK_CUR)

      # TODO: change IOError into ValueError
      with self.assertRaises(IOError):
        vshadow_store.seek_offset(-32 - volume_size, os.SEEK_END)

      # TODO: change IOError into ValueError
      with self.assertRaises(IOError):
        vshadow_store.seek_offset(0, -1)

    vshadow_volume.close()


if __name__ == "__main__":
  argument_parser = argparse.ArgumentParser()

  argument_parser.add_argument(
      "-o", "--offset", dest="offset", action="store", default=0,
      type=int, help="offset of the source file.")

  argument_parser.add_argument(
      "source", nargs="?", action="store", metavar="PATH",
      default=None, help="path of the source file.")

  options, unknown_options = argument_parser.parse_known_args()
  unknown_options.insert(0, sys.argv[0])

  setattr(unittest, "offset", options.offset)
  setattr(unittest, "source", options.source)

  unittest.main(argv=unknown_options, verbosity=2)
