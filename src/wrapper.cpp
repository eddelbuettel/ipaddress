#define ASIO_STANDALONE

#include <Rcpp.h>
#include "IpAddressVector.h"
#include "IpNetworkVector.h"

using namespace Rcpp;

// [[Rcpp::export]]
List parse_address_wrapper(CharacterVector x) {
  return IpAddressVector(x).asList();
}

// [[Rcpp::export]]
CharacterVector print_address_wrapper(List x) {
  return IpAddressVector(x).asCharacterVector();
}

// [[Rcpp::export]]
List parse_network_wrapper(CharacterVector x) {
  return IpNetworkVector(x).asList();
}

// [[Rcpp::export]]
CharacterVector print_network_wrapper(List x) {
  return IpNetworkVector(x).asCharacterVector();
}

// [[Rcpp::export]]
List netmask_wrapper(List x) {
  return IpNetworkVector(x).netmask().asList();
}

// [[Rcpp::export]]
List hostmask_wrapper(List x) {
  return IpNetworkVector(x).hostmask().asList();
}

// [[Rcpp::export]]
LogicalVector is_within_wrapper(List address_r, List network_r) {
  IpAddressVector address(address_r);
  IpNetworkVector network(network_r);

  return address.isWithin(network);
}

// [[Rcpp::export]]
LogicalVector is_within_any_wrapper(List address_r, List network_r) {
  IpAddressVector address(address_r);
  IpNetworkVector network(network_r);

  return address.isWithinAny(network);
}

// [[Rcpp::export]]
LogicalVector is_subnet_wrapper(List network1_r, List network2_r) {
  IpAddressVector address1(List::create(
      _["address1"] = network1_r["address1"],
      _["address2"] = network1_r["address2"],
      _["address3"] = network1_r["address3"],
      _["address4"] = network1_r["address4"],
      _["is_ipv6"] = network1_r["is_ipv6"]
  ));
  IpNetworkVector network2(network2_r);

  return address1.isWithin(network2);
}
