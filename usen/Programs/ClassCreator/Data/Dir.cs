using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

namespace ClassCreator.Data
{
    public class Dir
    {
        public Dir() { }
        public Dir(string path, string fullName, Dir parent) 
        {
            FullName = fullName;
            Path = path;
            Name = fullName.Replace($"{path}\\", "");
            Parent = parent;

            if (parent != null)
            {
                Root = parent.Root;
                PathSource = $"{parent.PathSource}\\{Name}";
            }
            else
            {
                Root = Name;
                PathSource = Name;
            }
        }

        public string Name { get; set; }
        public string FullName { get; set; }
        public string Path { get; set; }
        public string PathSource { get; set; }
        public string Root { get; set; }
        public Dir Parent { get; set; }
        public List<Dir> Subs { get; set; }
        public List<FileDescriptor> Files { get; set; }
    }
}
