/*
   Copyright 2011 hello.patz@gmail.com

   Licensed under the Apache License, Version 2.0 (the "License");
   you may not use this file except in compliance with the License.
   You may obtain a copy of the License at

       http://www.apache.org/licenses/LICENSE-2.0

   Unless required by applicable law or agreed to in writing, software
   distributed under the License is distributed on an "AS IS" BASIS,
   WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
   See the License for the specific language governing permissions and
   limitations under the License.
*/

using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.IO;

namespace Convert2UTF8
{
	class Program
	{
		static string[] header = { "*.h", "*.hpp", "*.inl", "*.hxx", "*.cs", };
		static string[] source = { "*.cpp", "*.cxx", };

		static void Main(string[] args)
		{
			string license = File.ReadAllText("license.txt").Trim();
			foreach (var postfix in header)
			{
				foreach (var f in new DirectoryInfo(@".").GetFiles(postfix, SearchOption.AllDirectories))
				{
					Encoding enc = Encoding.UTF8;
					if (f.Name == "targetver.h")
						enc = Encoding.ASCII;

					string s = File.ReadAllText(f.FullName);
					if (s.Length >= 5)
					{
						var sub = s.Trim().Substring(0, 2);
						if (sub != "/*")
							s = license + Environment.NewLine + Environment.NewLine + s;
					}
					
					File.WriteAllText(f.FullName, s, enc);
				}
			}
			foreach (var postfix in source)
			{
				foreach (var f in new DirectoryInfo(@".").GetFiles(postfix, SearchOption.AllDirectories))
				{
					Encoding enc = Encoding.UTF8;

					string s = File.ReadAllText(f.FullName);
					File.WriteAllText(f.FullName, s, enc);
				}
			}
		}
	}
}
