#pragma once
#ifndef FINITY_GUI_FILEBROWSER_H
#define FINITY_GUI_FILEBROWSER_H

#include <array>
#include <functional>
#include <memory>
#include <string>
#include <vector>
#include "../panels/FileBrowser.h"

using std::string;

enum ImGuiFileBrowserFlags {
    IMGUI_FILE_BROWSER_SELECT_DIR = 0,
    IMGUI_FILE_BROWSER_ENTER_NEW_FILENAME,
    IMGUI_FILE_BROWSER_NO_MODAL,
    IMGUI_FILE_BROWSER_NO_TITLEBAR,
    IMGUI_FILE_BROWSER_NO_STATUSBAR,
    IMGUI_FILE_BROWSER_CLOSE_ONESC,
    IMGUI_FILE_BROWSER_CREATE_NEW_DIR
};

namespace Finity { namespace GUI { namespace Windows {
    class FileBrowser: public ImGui::FileBrowser {
    public:
        explicit FileBrowser(ImGuiFileBrowserFlags flag=0);
        FileBrowser(const FileBrowser &copyFrom);
        FileBrowser &operator=(const FileBrowser &copyFrom);
        void SetWindowSize(int width, int height);
        void SetTitle(string title);
        void SetCancelText(string cancel);
        void SetOkText(string ok);
        void Open();
        void Close();
        bool IsOpened() const noexcept;
        void Refresh() { SetPwd(); }
        void ClearSelected();
        void ClearFilters();
        void SetLabels();
        void SetFileFilters(const std::vector<const char*>& fileFilters);

    private:
        class ScopeGuard {
            std::function<void()> func_;

        public:
            template<typename T>
            explicit ScopeGuard(T func) : func_(std::move(func)) {}
            ~ScopeGuard() { func_(); }
        };

        void SetPwdUncatched(const FS::Path &pwd);

        int mwidth;
        int mheight;
        ImGuiFileBrowserFlags flags;

        string mtitle;
        string mOpenLabel;
        string mokText;
        string mCancel;
        string statuStr;

        const char* newFolderLabel = "+";
        const char* directoryLabel = "[D]";
        const char* fileLabel = "[F]";

        bool openFlag;
        bool closeFlag;
        bool isOpened;
        bool ok;

        std::vector<const char*> typeFilters;
        int typeFilterIndex;

        FS::Path pwd;
        FS::Path selectedFilename;

        struct FileRecord {
            bool isDir = false;
            FS::Path name;
            string showName;
            FS::Path extension;
        };
        std::vector<FileRecord> fileRecords;

        // IMPROVE: overflow when selectedFilename.length() > inputNameBuff.size() - 1
        static constexpr size_t INPUT_NAME_BUF_SIZE = 512;
        std::unique_ptr<std::array<char, INPUT_NAME_BUF_SIZE>> inputNameBuf;
        std::unique_ptr<std::array<char, INPUT_NAME_BUF_SIZE>> newDirNameBuffer;
        string openNewDirLabel;

    };
}
}}

#endif //FINITY_GUI_FILEBROWSER_H
