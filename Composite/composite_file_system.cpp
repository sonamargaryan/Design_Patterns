#include <iostream>
#include <vector>
#include <string>
#include <memory>

class FileSystemNode {
protected:
    std::string name;
public:
    FileSystemNode(const std::string& n) : name(n) {}
    virtual ~FileSystemNode() = default;

    virtual int getSize() const = 0;
    virtual void print(int indent = 0) const = 0;
    
    std::string getName() const { return name; }
};

class File : public FileSystemNode {
private:
    int size;
public:
    File(const std::string& name, int s) : FileSystemNode(name), size(s) {}

    int getSize() const override {
        return size;
    }

    void print(int indent = 0) const override {
        std::string spaces(indent, ' ');
        std::cout << spaces << "- [File] " << name << " (" << size << " KB)\n";
    }
};

class Directory : public FileSystemNode {
private:
    std::vector<std::shared_ptr<FileSystemNode>> children;
public:
    Directory(const std::string& name) : FileSystemNode(name) {}

    void addNode(std::shared_ptr<FileSystemNode> node) {
        if (node.get() == this) {
            std::cerr << "Cannot add a directory to itself!\n";
            return;
        }
        children.push_back(node);
    }

    int getSize() const override {
        int totalSize = 0;
        for (const auto& child : children) {
            totalSize += child->getSize();
        }
        return totalSize;
    }

    void print(int indent = 0) const override {
        std::string spaces(indent, ' ');
        std::cout << spaces << "+ [Directory] " << name << "\n";
        for (const auto& child : children) {
            child->print(indent + 4);
        }
    }
};

int main() {
    auto file1 = std::make_shared<File>("document.txt", 15);
    auto file2 = std::make_shared<File>("photo.jpg", 250);
    auto file3 = std::make_shared<File>("song.mp3", 3500);

    auto mediaFolder = std::make_shared<Directory>("Media");
    mediaFolder->addNode(file2);
    mediaFolder->addNode(file3);

    auto rootFolder = std::make_shared<Directory>("Root_C");
    rootFolder->addNode(file1);
    rootFolder->addNode(mediaFolder); 
  
    std::cout << "--- File System Structure ---\n";
    rootFolder->print();

    std::cout << "\nTotal size of '" << rootFolder->getName() << "': " 
              << rootFolder->getSize() << " KB\n";

    return 0;
}
