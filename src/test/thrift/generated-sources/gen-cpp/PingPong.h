/*   Copyright (C) 2013-2014 Computer Sciences Corporation
 *
 * Licensed under the Apache License, Version 2.0 (the "License");
 * you may not use this file except in compliance with the License.
 * You may obtain a copy of the License at
 *
 *     http://www.apache.org/licenses/LICENSE-2.0
 *
 * Unless required by applicable law or agreed to in writing, software
 * distributed under the License is distributed on an "AS IS" BASIS,
 * WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 * See the License for the specific language governing permissions and
 * limitations under the License. */

/**
 * Autogenerated by Thrift Compiler (0.9.1)
 *
 * DO NOT EDIT UNLESS YOU ARE SURE THAT YOU KNOW WHAT YOU ARE DOING
 *  @generated
 */
#ifndef PingPong_H
#define PingPong_H

#include <thrift/TDispatchProcessor.h>
#include "PingPong_types.h"



class PingPongIf {
 public:
  virtual ~PingPongIf() {}
  virtual void ping(std::string& _return) = 0;
};

class PingPongIfFactory {
 public:
  typedef PingPongIf Handler;

  virtual ~PingPongIfFactory() {}

  virtual PingPongIf* getHandler(const ::apache::thrift::TConnectionInfo& connInfo) = 0;
  virtual void releaseHandler(PingPongIf* /* handler */) = 0;
};

class PingPongIfSingletonFactory : virtual public PingPongIfFactory {
 public:
  PingPongIfSingletonFactory(const boost::shared_ptr<PingPongIf>& iface) : iface_(iface) {}
  virtual ~PingPongIfSingletonFactory() {}

  virtual PingPongIf* getHandler(const ::apache::thrift::TConnectionInfo&) {
    return iface_.get();
  }
  virtual void releaseHandler(PingPongIf* /* handler */) {}

 protected:
  boost::shared_ptr<PingPongIf> iface_;
};

class PingPongNull : virtual public PingPongIf {
 public:
  virtual ~PingPongNull() {}
  void ping(std::string& /* _return */) {
    return;
  }
};


class PingPong_ping_args {
 public:

  PingPong_ping_args() {
  }

  virtual ~PingPong_ping_args() throw() {}


  bool operator == (const PingPong_ping_args & /* rhs */) const
  {
    return true;
  }
  bool operator != (const PingPong_ping_args &rhs) const {
    return !(*this == rhs);
  }

  bool operator < (const PingPong_ping_args & ) const;

  uint32_t read(::apache::thrift::protocol::TProtocol* iprot);
  uint32_t write(::apache::thrift::protocol::TProtocol* oprot) const;

};


class PingPong_ping_pargs {
 public:


  virtual ~PingPong_ping_pargs() throw() {}


  uint32_t write(::apache::thrift::protocol::TProtocol* oprot) const;

};

typedef struct _PingPong_ping_result__isset {
  _PingPong_ping_result__isset() : success(false) {}
  bool success;
} _PingPong_ping_result__isset;

class PingPong_ping_result {
 public:

  PingPong_ping_result() : success() {
  }

  virtual ~PingPong_ping_result() throw() {}

  std::string success;

  _PingPong_ping_result__isset __isset;

  void __set_success(const std::string& val) {
    success = val;
  }

  bool operator == (const PingPong_ping_result & rhs) const
  {
    if (!(success == rhs.success))
      return false;
    return true;
  }
  bool operator != (const PingPong_ping_result &rhs) const {
    return !(*this == rhs);
  }

  bool operator < (const PingPong_ping_result & ) const;

  uint32_t read(::apache::thrift::protocol::TProtocol* iprot);
  uint32_t write(::apache::thrift::protocol::TProtocol* oprot) const;

};

typedef struct _PingPong_ping_presult__isset {
  _PingPong_ping_presult__isset() : success(false) {}
  bool success;
} _PingPong_ping_presult__isset;

class PingPong_ping_presult {
 public:


  virtual ~PingPong_ping_presult() throw() {}

  std::string* success;

  _PingPong_ping_presult__isset __isset;

  uint32_t read(::apache::thrift::protocol::TProtocol* iprot);

};

class PingPongClient : virtual public PingPongIf {
 public:
  PingPongClient(boost::shared_ptr< ::apache::thrift::protocol::TProtocol> prot) :
    piprot_(prot),
    poprot_(prot) {
    iprot_ = prot.get();
    oprot_ = prot.get();
  }
  PingPongClient(boost::shared_ptr< ::apache::thrift::protocol::TProtocol> iprot, boost::shared_ptr< ::apache::thrift::protocol::TProtocol> oprot) :
    piprot_(iprot),
    poprot_(oprot) {
    iprot_ = iprot.get();
    oprot_ = oprot.get();
  }
  boost::shared_ptr< ::apache::thrift::protocol::TProtocol> getInputProtocol() {
    return piprot_;
  }
  boost::shared_ptr< ::apache::thrift::protocol::TProtocol> getOutputProtocol() {
    return poprot_;
  }
  void ping(std::string& _return);
  void send_ping();
  void recv_ping(std::string& _return);
 protected:
  boost::shared_ptr< ::apache::thrift::protocol::TProtocol> piprot_;
  boost::shared_ptr< ::apache::thrift::protocol::TProtocol> poprot_;
  ::apache::thrift::protocol::TProtocol* iprot_;
  ::apache::thrift::protocol::TProtocol* oprot_;
};

class PingPongProcessor : public ::apache::thrift::TDispatchProcessor {
 protected:
  boost::shared_ptr<PingPongIf> iface_;
  virtual bool dispatchCall(::apache::thrift::protocol::TProtocol* iprot, ::apache::thrift::protocol::TProtocol* oprot, const std::string& fname, int32_t seqid, void* callContext);
 private:
  typedef  void (PingPongProcessor::*ProcessFunction)(int32_t, ::apache::thrift::protocol::TProtocol*, ::apache::thrift::protocol::TProtocol*, void*);
  typedef std::map<std::string, ProcessFunction> ProcessMap;
  ProcessMap processMap_;
  void process_ping(int32_t seqid, ::apache::thrift::protocol::TProtocol* iprot, ::apache::thrift::protocol::TProtocol* oprot, void* callContext);
 public:
  PingPongProcessor(boost::shared_ptr<PingPongIf> iface) :
    iface_(iface) {
    processMap_["ping"] = &PingPongProcessor::process_ping;
  }

  virtual ~PingPongProcessor() {}
};

class PingPongProcessorFactory : public ::apache::thrift::TProcessorFactory {
 public:
  PingPongProcessorFactory(const ::boost::shared_ptr< PingPongIfFactory >& handlerFactory) :
      handlerFactory_(handlerFactory) {}

  ::boost::shared_ptr< ::apache::thrift::TProcessor > getProcessor(const ::apache::thrift::TConnectionInfo& connInfo);

 protected:
  ::boost::shared_ptr< PingPongIfFactory > handlerFactory_;
};

class PingPongMultiface : virtual public PingPongIf {
 public:
  PingPongMultiface(std::vector<boost::shared_ptr<PingPongIf> >& ifaces) : ifaces_(ifaces) {
  }
  virtual ~PingPongMultiface() {}
 protected:
  std::vector<boost::shared_ptr<PingPongIf> > ifaces_;
  PingPongMultiface() {}
  void add(boost::shared_ptr<PingPongIf> iface) {
    ifaces_.push_back(iface);
  }
 public:
  void ping(std::string& _return) {
    size_t sz = ifaces_.size();
    size_t i = 0;
    for (; i < (sz - 1); ++i) {
      ifaces_[i]->ping(_return);
    }
    ifaces_[i]->ping(_return);
    return;
  }

};



#endif
