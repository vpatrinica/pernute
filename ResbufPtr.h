#pragma once

class CResbufPtr {
  resbuf* pHead; // Maintain a pointer to the head of the resource chain for de-allocation
  resbuf* pBuffer;
public:
  CResbufPtr(resbuf* ptr) : pHead(ptr), pBuffer(ptr) {}
  ~CResbufPtr() {
    acutRelRb(pHead); // release the buffer
    pHead = pBuffer = 0;
  }
  resbuf* operator->() { return pBuffer; }  // so you can do things like buf->resval.rstring
  operator resbuf*() { return pBuffer; } // so you can pass the smart pointer to functions that expect a resbuf*
  bool isNull() { return pBuffer == 0; } // null pointer check
  void start() { pBuffer = pHead; } // in case you need to return to the head of the resource chain
  void next() { pBuffer = pBuffer->rbnext; } // try to move the pointer to the next item in the resource chain
};
