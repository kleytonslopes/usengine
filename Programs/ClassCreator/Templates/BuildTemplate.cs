using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;
using System.IO;
using System.Reflection;
using ClassCreator.Data;

namespace ClassCreator.Templates
{
    public class BuildTemplate
    {
        private string classNameCpp = string.Empty;
        private string classHeadPath = string.Empty;
        
        private string classNameHpp = string.Empty;
        private string classDefinition = string.Empty;
        private string className = string.Empty;
        private string classBaseName = string.Empty;
        private string baseClassDefinition = string.Empty;

        private string classGenNameHpp = string.Empty;
        private string classGenDefineIdentity = string.Empty;
        private string classGenVersion = string.Empty;

        private string creationDate = string.Empty;

        public string GenerateClassCpp(ClassData classData)
        {
            Assembly assembly = Assembly.GetExecutingAssembly();
            string resSrcFile = "ClassCreator.Templates.ClassCppTemplate.txt";
            string fileBody;
            using (Stream stream = assembly.GetManifestResourceStream(resSrcFile))
            {
                using (StreamReader reader = new StreamReader(stream))
                {
                    fileBody = reader.ReadToEnd();
                }
            }

            fileBody = fileBody.Replace("{classNameCpp}", classData.CppFileName)
                    .Replace("{creationDate}", classData.DateCreation)
                    .Replace("{classHeadPath}", classData.GetClassHeadPath());

            return fileBody;
        }

        public string GenerateClassHpp(ClassData classData)
        {
            Assembly assembly = Assembly.GetExecutingAssembly();
            string resSrcFile = "ClassCreator.Templates.ClassHppTemplate.txt";
            string fileBody;
            using (Stream stream = assembly.GetManifestResourceStream(resSrcFile))
            {
                using (StreamReader reader = new StreamReader(stream))
                {
                    fileBody = reader.ReadToEnd();
                }
            }

            fileBody = fileBody.Replace("{classNameHpp}", classData.HppFileName)
                    .Replace("{creationDate}", classData.DateCreation)
                    .Replace("{classDefinition}", classData.ClassDefinition)
                    .Replace("{genIncludeDefine}", classData.GetGenInclude())
                    .Replace("{className}", classData.ClassName)
                    .Replace("{genBody}", classData.GetGenBobdy())
                    .Replace("{baseClassInclude}", classData.BaseClassInclude)
                    .Replace("{baseClassDefinition}", classData.BaseClassTemplate);

            return fileBody;
        }

        public string GenerateClassGen(ClassData classData)
        {
            Assembly assembly = Assembly.GetExecutingAssembly();
            string resSrcFile = "ClassCreator.Templates.ClassGenTemplate.txt";
            string fileBody;
            using (Stream stream = assembly.GetManifestResourceStream(resSrcFile))
            {
                using (StreamReader reader = new StreamReader(stream))
                {
                    fileBody = reader.ReadToEnd();
                }
            }

            fileBody = fileBody.Replace("{classNameHpp}", classData.HppFileName)
                    .Replace("{classGenNameHpp}", classData.GenFileName)
                    .Replace("{creationDate}", classData.DateCreation)
                    .Replace("{className}", classData.ClassName)
                    .Replace("{classNameCpp}", classData.CppFileName)
                    .Replace("{classNameHpp}", classData.HppFileName)
                    .Replace("{classNameHpp}", classData.HppFileName)
                    .Replace("{classDefinition}", classData.ClassDefinition)
                    .Replace("{classHeadPath}", classData.GetClassHeadPath())
                    .Replace("{classGenDefineIdentity}", classData.ClassGenDefinition)
                    .Replace("{classGenVersion}", classData.ClassGenDefinitionVersion)
                    .Replace("{classBaseName}", classData.BaseClassName)
                    .Replace("{classBasePath}", classData.BaseClassPathHpp)
                    .Replace("{superClassTemplate}", classData.GetSuperTemplate())
                    ;

            return fileBody;
        }
    }
}
