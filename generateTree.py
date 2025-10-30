import os
import re

def parseClasses(headerPath):
    with open(headerPath, 'r') as f:
        content = f.read()
    classes = []
    classPattern = re.compile(r'class\s+(\w+)(\s*:\s*public\s+(\w+))?\s*{([^}]*)}', re.DOTALL)
    for match in classPattern.finditer(content):
        name = match.group(1)
        base = match.group(3)
        body = match.group(4)
        memberPattern = re.compile(r'((?:int|float|double|enum|[\w:]+(?:\s*\*)?)+)\s+(\w+)(?:\s*=\s*[^;]+)?;')
        members = [f"{m[0].strip()} {m[1]}" for m in memberPattern.findall(body)]
        methodPattern = re.compile(r'((?:[\w:]+(?:\s*\*)?)+)\s+(\w+)\s*\(([^;{)]*)\)\s*(?:const)?\s*;')
        methods = [f"{m[0].strip()} {m[1]}({m[2].strip()})" for m in methodPattern.findall(body)]
        classes.append({'name': name, 'base': base, 'members': members, 'methods': methods})
    return classes

def buildTree(classes):
    tree = {}
    for cls in classes:
        tree[cls['name']] = {'base': cls['base'], 'members': cls['members'], 'methods': cls['methods']}
    return tree

def printTree(tree, file=None):
    def printNode(name, prefix="", isLast=True, isRoot=False):
        node = tree[name]
        branch = "└── " if isLast else "├── "
        line = f"{prefix}{branch}{name}"
        print(line) if file is None else print(line, file=file)
        childPrefix = prefix + ("    " if isLast else "│   ")
        # Print members and methods with branch lines
        if node['members']:
            line = f"{childPrefix}├─ Members:"
            print(line) if file is None else print(line, file=file)
            for i, m in enumerate(node['members']):
                isLastMember = (i == len(node['members']) - 1) and not node['methods']
                memberBranch = "└─ " if isLastMember else "├─ "
                line = f"{childPrefix}{memberBranch}  {m}"
                print(line) if file is None else print(line, file=file)
        if node['methods']:
            line = f"{childPrefix}├─ Methods:"
            print(line) if file is None else print(line, file=file)
            for i, m in enumerate(node['methods']):
                isLastMethod = (i == len(node['methods']) - 1)
                methodBranch = "└─ " if isLastMethod else "├─ "
                line = f"{childPrefix}{methodBranch}  {m}"
                print(line) if file is None else print(line, file=file)
        # Find children
        children = [child for child, data in tree.items() if data['base'] == name]
        for i, child in enumerate(children):
            # Add separation only between siblings, not before the first child
            if i > 0:
                line = f"{childPrefix}│"
                print(line) if file is None else print(line, file=file)
            printNode(child, childPrefix, i == len(children) - 1)
        # Add separation only between root classes, not after the last root
        if isRoot and not isLast:
            line = f"│"
            print(line) if file is None else print(line, file=file)

    roots = [name for name, data in tree.items() if not data['base']]
    for i, root in enumerate(roots):
        printNode(root, "", i == len(roots) - 1, isRoot=True)

if __name__ == "__main__":
    # folder = "dspLib"
    folder = os.getcwd()
    allClasses = []
    for fname in os.listdir(folder):
        if fname.endswith('.hpp'):
            allClasses.extend(parseClasses(os.path.join(folder, fname)))
    classTree = buildTree(allClasses)
    with open("dspLib Tree.txt", "w") as f:
        printTree(classTree, file=f)
    printTree(classTree)
