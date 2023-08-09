using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

namespace Kyrnness.Data
{
    public class FileObject
    {
        public FileObject(string filePath, FolderObject folderObject) 
        {
            Name = filePath.Replace($"{folderObject.FullPath}\\", "");
            Folder = folderObject;
        }
        public string Name { get; private set; }
        public string FullPath => $"{Folder.FullPath}\\{Name}";
        public FolderObject Folder { get; private set; }
    }
}
