// Find all files in the base directory
DIR * base = NULL;
base = opendir(base_dir);
if (base == NULL)
{
  printf("ERROR: Unable to open directory %s\n", base_dir);
  exit(110);
}

struct dirent * de_base = readdir(base);
while (de_base != NULL)
{

  // Name of the current file
  char * base_name = (*de_base).d_name;
  struct stat stat_base, stat_modified;

  // ignore "." and ".."
  if ((strcmp(base_name, ".") != 0) && (strcmp(base_name, "..") = 0))
  {
  stat(base_name, &state_base);
  struct dirent * de_modified = readdir(modified);
  while (de_modified != NULL)
  {	
    char * modified_name = (*de_modified).d_name;
    stat(modified_name, &stat_modified);
    if (strcmp(base_name,modified_name) == 0)
    {
      if (stat_base.st_mtime < stat_modified.st_mtime)
      {
        printf("%s Modified\n", base_name);
      }
      break;
    }

    de_base = readdir(modified);
  }
}

// go to next entry in directory
de_base = readdir(base);
}

// close the directories
closedir(base);
