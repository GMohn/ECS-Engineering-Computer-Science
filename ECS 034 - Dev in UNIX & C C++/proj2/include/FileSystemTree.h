#ifndef FILESYSTEMTREE_H 	  			 	 
#define FILESYSTEMTREE_H

#include <string>
#include <iterator>
#include <memory>
#include <vector>

class CFileSystemTree{
    protected:
        struct SImplementation;
        std::shared_ptr< SImplementation > DImplementation;

    public:
        class CEntryIterator;
        class CConstEntryIterator;

        class CEntry{
            friend class CFileSystemTree;
            friend class CEntryIterator;
            friend class CConstEntryIterator;
            protected:
                struct SImplementation;
                std::shared_ptr< SImplementation > DImplementation;

                CEntry();
                ~CEntry();
                
            public:
                bool Valid() const;
                std::string Name() const;
                std::string FullPath() const;
				
                std::string ToString() const;
                operator std::string() const;

                bool Rename(const std::string &name);

                size_t ChildCount() const;
                bool SetChild(const std::string &name, const CEntryIterator &iter);
                bool AddChild(const std::string &name);
                bool AddPath(const std::string &path);
                bool RemoveChild(const std::string &name);

                bool SetData(const std::vector< char > &data);
                bool GetData(std::vector< char > &data) const;

                CEntryIterator Parent();
                CConstEntryIterator Parent() const;

                CEntryIterator Find(const std::string &path);
                CConstEntryIterator Find(const std::string &path) const;
                CEntryIterator begin();
                CConstEntryIterator begin() const;
                CConstEntryIterator cbegin() const;
                CEntryIterator end();
                CConstEntryIterator end() const;
                CConstEntryIterator cend() const;
        };

        class CEntryIterator{
            friend class CFileSystemTree;
            friend class CEntry;
            friend class CConstEntryIterator;
            protected:
                struct SImplementation;
                std::unique_ptr< SImplementation > DImplementation;

            public:
                CEntryIterator();
                CEntryIterator(const CEntryIterator &iter);
                ~CEntryIterator();

                CEntryIterator& operator=(const CEntryIterator  &iter);
                bool operator==(const CEntryIterator &iter) const;
                bool operator!=(const CEntryIterator &iter) const;

                CEntryIterator& operator++();
                CEntryIterator operator++(int);
                CEntryIterator& operator--();
                CEntryIterator operator--(int);

                CEntry *operator->() const;
        };

        class CConstEntryIterator{
            friend class CFileSystemTree;
            protected:
                struct SImplementation;
                std::unique_ptr< SImplementation > DImplementation;

            public:
                CConstEntryIterator();
                CConstEntryIterator(const CConstEntryIterator &iter);
                CConstEntryIterator(const CEntryIterator &iter);
                ~CConstEntryIterator();

                CConstEntryIterator& operator=(const CConstEntryIterator &iter);
                bool operator==(const CConstEntryIterator &iter) const;
                bool operator!=(const CConstEntryIterator &iter) const;

                CConstEntryIterator& operator++();
                CConstEntryIterator operator++(int);
                CConstEntryIterator& operator--();
                CConstEntryIterator operator--(int);

                const CEntry *operator->() const;
        };

        CFileSystemTree();
        CFileSystemTree(const CFileSystemTree &tree) = delete;
        ~CFileSystemTree();

        CFileSystemTree &operator=(const CFileSystemTree &tree) = delete;
        
        CEntryIterator Root();
        CConstEntryIterator Root() const;

        std::string ToString() const;
        operator std::string() const;

        CEntryIterator Find(const std::string &path);
        CConstEntryIterator Find(const std::string &path) const;

        CEntryIterator NotFound();
        CConstEntryIterator NotFound() const;

};

#endif
