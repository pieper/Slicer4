#ifndef __vtkDataFileFormatHelper_h
#define __vtkDataFileFormatHelper_h

#include "vtkObject.h"
#include "vtkObjectFactory.h"
#include "vtkMRML.h"

class vtkStringArray;

typedef struct
{
  const char *ClassName;
  const char *Description;
  const char *GenericName;
  const char *Extension;
} ITKImageFileFormat;

class VTK_MRML_EXPORT vtkDataFileFormatHelper : public vtkObject 
{
  public:
  
  /// The Usual vtk class functions
  static vtkDataFileFormatHelper *New();
  vtkTypeRevisionMacro(vtkDataFileFormatHelper, vtkObject);
  void PrintSelf(ostream& os, vtkIndent indent);

  static const char* GetFileExtensionFromFormatString(
   const char* fileformat);
  const char* GetClassNameFromFormatString(
   const char* fileformat);
  
  /// 
  /// Get the itkimageio supported file formats.
  //vtkGetObjectMacro ( ITKSupportedWriteFileFormats, vtkStringArray);
  virtual vtkStringArray* GetITKSupportedWriteFileFormats();
  virtual vtkStringArray* GetITKSupportedReadFileFormats()
    {
    return NULL;
    }
  virtual vtkStringArray* GetITKSupportedWriteFileExtensions();
  virtual const char* GetITKSupportedExtensionGenericNameByIndex(int idx);
  virtual const char* GetITKSupportedExtensionClassNameByIndex(int idx);

//BTX
 protected:
  vtkDataFileFormatHelper();
  virtual ~vtkDataFileFormatHelper();

  vtkStringArray* SupportedWriteFileExtensions;
  vtkStringArray* SupportedWriteFileGenericNames;
  vtkStringArray* SupportedWriteFileClassNames;
  vtkStringArray* ITKSupportedWriteFileFormats;

  /// This will initialize the supported file formats
  virtual void InitializeITKSupportedFileFormats();
  virtual void PopulateITKSupportedWriteFileTypes();
  virtual void AddSupportedWriterFileFormat(
     ITKImageFileFormat& structFileFormat);
     
private:
  vtkDataFileFormatHelper(const vtkDataFileFormatHelper&);
  void operator=(const vtkDataFileFormatHelper&);
//ETX
};

#endif
