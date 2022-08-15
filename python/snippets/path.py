import pathlib
import sys

cwd = pathlib.Path.cwd()
home = pathlib.Path.home()
user_dir = pathlib.Path(sys.argv[1])


def tree(directory):
    """
    Print a directory tree based on the directory input

    Always recursive
    """
    print(f"+ {directory}")
    for path in sorted(directory.rglob("*")):
        depth = len(path.relative_to(directory).parts)
        spacer = "    " * depth
        print(f"{spacer}+ {path.name}")


def file_list(directory):
    """
    Get a list of files from a directory

    Returns a list of files, sorted
    """
    files = sorted(directory.glob("*"))

    return files


if __name__ == "__main__":
    files = file_list(user_dir)
    for file in files:
        if file.is_dir():
            print(f"Directory: {file}")
        else:
            print(f"File: {file}")
