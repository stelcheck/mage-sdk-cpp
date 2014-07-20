#ifndef MAGERPC_H
#define MAGERPC_H

#include "exceptions.h"
#include <iostream>
#include <functional>
#include <future>
#include <jsonrpc/rpc.h>

namespace mage
{
	class RPC
	{
		public:
			RPC(const std::string &mageApplication,
			    const std::string &mageDomain = "localhost:8080",
			    const std::string &mageProtocol = "http");
			~RPC();

			virtual Json::Value Call(const std::string &name,
			                         const Json::Value &params) const;
			virtual std::future<Json::Value> Call(const std::string &name,
			                                      const Json::Value &params,
			                                      bool doAsync) const;
			virtual void Call(const std::string &name,
			                  const Json::Value &params,
			                  const std::function<void(mage::MageError, Json::Value)>& callback,
			                  bool doAsync) const;
			virtual void RegisterCallback(const std::string &eventName,
			                              std::function<void(Json::Value)> callback);

			void SetProtocol(const std::string &mageProtocol);
			void SetDomain(const std::string &mageDomain);
			void SetApplication(const std::string &mageApplication);
			void SetSession(const std::string &sessionKey) const;
			void ClearSession() const;

			std::string GetUrl() const;

		private:
			std::string protocol;
			std::string domain;
			std::string application;

			jsonrpc::HttpClient *httpClient;
			jsonrpc::Client     *jsonRpcClient;
	};

} /* namespace mage */
#endif /* MAGERPC_H */
