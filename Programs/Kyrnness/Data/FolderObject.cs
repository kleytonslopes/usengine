using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

namespace Kyrnness.Data
{
    public class FolderObject
    {
        public FolderObject(string name, string fullPath, FolderObject parent)
        {
            this.ParentFolder = parent;
            this.FullPath = fullPath;
            this.Name = name;
        }

        public string Name { get; private set; }
        public string FullPath { get; private set; }
        public string Path
        {
            get
            {
                string path = string.Empty;
                if(this.ParentFolder != null)
                {
                    path = $"{ParentFolder.Path}/{Name}";

                    if (path[0] == '/')
                        path = path.Substring(1);
                }

                return path;
            }
        }
        public FolderObject ParentFolder { get; private set; }
        public List<FolderObject> SubFolders { get; set; }
        public List<FileObject> Files { get; set; }
    }
}
