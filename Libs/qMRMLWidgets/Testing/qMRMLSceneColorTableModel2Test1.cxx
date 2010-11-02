/*==============================================================================

  Program: 3D Slicer

  Copyright (c) 2010 Kitware Inc.

  See Doc/copyright/copyright.txt
  or http://www.slicer.org/copyright/copyright.txt for details.

  Unless required by applicable law or agreed to in writing, software
  distributed under the License is distributed on an "AS IS" BASIS,
  WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
  See the License for the specific language governing permissions and
  limitations under the License.

  This file was originally developed by Julien Finet, Kitware Inc.
  and was partially funded by NIH grant 3P41RR013218-12S1

==============================================================================*/

// QT includes
#include <QApplication>
#include <QDebug>
#include <QString>
#include <QStringList>
#include <QTreeView>

// CTK includes
#include <ctkModelTester.h>

// qMRML includes
#include "qMRMLNodeFactory.h"
#include "qMRMLSceneColorTableModel2.h"

#include "TestingMacros.h"
// MRML includes
#include <vtkEventBroker.h>
#include <vtkMRMLColorTableNode.h>

// VTK includes
#include <vtkSmartPointer.h>

// STD includes
#include <cstdlib>
#include <iostream>

int qMRMLSceneColorTableModel2Test1(int argc, char * argv [])
{
  QApplication app(argc, argv);

  qMRMLSceneColorTableModel2 model;
  model.setListenNodeModifiedEvent(true);

  vtkSmartPointer<vtkMRMLScene> scene = vtkSmartPointer<vtkMRMLScene>::New();
  qMRMLNodeFactory nodeFactory(0);
  nodeFactory.setMRMLScene(scene);
  nodeFactory.addAttribute("Category", "First category");
  vtkMRMLNode* node = nodeFactory.createNode("vtkMRMLColorTableNode");
  vtkMRMLColorTableNode* colorNode = vtkMRMLColorTableNode::SafeDownCast(node);
  if (colorNode)
    {
    colorNode->SetTypeToWarmShade1();
    }
  model.setMRMLScene(scene);
  colorNode->SetTypeToCool1();

  QTreeView* view = new QTreeView(0);
  view->setModel(&model);
  view->show();
  view->resize(500, 800);

  return app.exec();
}

