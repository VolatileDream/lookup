# `lookup`

A tiny C utility to find local project configuration files/folders.

---

A lot of projects store project specific settings in a `.$NAME` file or folder.
`lookup` is the tiny little program that you would use to find this file or
folder at the root of your project directory.

It's designed to be easily included in any sort of script, supporting only a
single argument.

### invoking

```
# when in a project that has "file-or-folder-name" at it's root
> lookup file-or-folder-name || echo "default-value"
/some/path/to/your/project/root/file-or-folder-name

# when a project doesn't have the config file/folder
> lookup no-config || echo "/user/home/folder/default-value"
/user/home/folder/default-value

```

