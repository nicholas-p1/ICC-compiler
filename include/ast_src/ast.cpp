#include "ast.hpp"

void AST::generateFrames(Frame* _frame){
    throw std::runtime_error("AST: generateFrames Not implemented yet by child class.\n");
}

void AST::compile(std::ostream &assemblyOut) {
    throw std::runtime_error("AST: compile Not implemented yet by child class.\n");
}

void AST::updateVariable(std::ostream &assemblyOut, Frame* currentFrame, std::string reg) {
    throw std::runtime_error("AST: updateVariable Not implemented by child class.\n");
}

AST::~AST() {
    delete frame;
}

Frame::Frame(Frame* _parentFrame) :
    parentFrame(_parentFrame)
{}

Frame::~Frame() {
    delete parentFrame;
}

int Frame::getVarPos(const std::string &variableName) const{
    auto variableBinding = variableBindings.find(variableName);
    if (variableBinding != variableBindings.end()) {
        return variableBinding->second;
    }
    return -1;
}

std::pair<int, int> Frame::getVarAddress(const std::string &variableName) {
    int depth = 0;
    Frame* frame = this;
    int pos = frame->getVarPos(variableName);
    while(pos == -1){
        depth++;
        frame = frame->parentFrame;
        pos = frame->getVarPos(variableName);
    }
    return {depth, pos};
}

void Frame::addVariable(const std::string &variableName, int bitSize) {
    variableBindings[variableName] = memOcc;
    memOcc += bitSize + bitSize%8;
}

int Frame::getStoreSize() const {
    return storeSize;
}

int Frame::getVarSize() const {
    return memOcc;
}

void Frame::setLoopLabelNames(std::string _startLoopLabelName, std::string _endLoopLabelName) {
    startLoopLabelName = _startLoopLabelName;
    endLoopLabelName = _endLoopLabelName;
}

void Frame::addCaseLabelValueMapping(std::string label, int value) {
    caseLabelValueMapping[label] = value;
}

std::unordered_map<std::string, int> Frame::getCaseLabelValueMapping() const {
    return caseLabelValueMapping;
}

int Frame::getDistanceToFun(){
    int i = 0;
    Frame* frame = this;
    while(!frame->isFun){
        i++;
        frame = frame->parentFrame;
    }
    return i;
}

std::pair<std::string, int> Frame::getStartLoopLabelName(std::ostream &assemblyOut) {
    int i = 0;
    Frame* frame = this;
    while (frame->startLoopLabelName == "") {
        // variable does not exist in current frame
        // try to find in parent frame
        i++;
        frame = frame->parentFrame;
    }

    return {frame->startLoopLabelName, i};
}

std::pair<std::string, int> Frame::getEndLoopLabelName(std::ostream &assemblyOut) {
    int i = 0;
    Frame* frame = this;
    while (frame->endLoopLabelName == "") {
        // variable does not exist in current frame
        // try to find in parent frame
        i++;
        frame = frame->parentFrame;
    }

    return {frame->endLoopLabelName, i};
}
