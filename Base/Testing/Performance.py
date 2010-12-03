
comment = """
import os
execfile(os.environ['Slicer_HOME'] + "/../../Slicer4/Base/Testing/Performance.py")
"""

def reslicing(iters=1000):
  """ go into a loop that stresses the reslice performance
  """
  sliceNode = getNodes()['redAxial']
  for i in xrange(iters):
    sliceNode.SetSliceOffset(20)
    app().processEvents()
    sliceNode.SetSliceOffset(80)
    app().processEvents()
  
