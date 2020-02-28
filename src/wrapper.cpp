#include <Rcpp.h>
#include "IpAddressVector.h"
#include "IpNetworkVector.h"

using namespace Rcpp;

/*------------------------
 *  Encoding and decoding
 * -----------------------
 */
// [[Rcpp::export]]
List parse_address_wrapper(CharacterVector x) {
  return IpAddressVector(x).encodeR();
}

// [[Rcpp::export]]
CharacterVector print_address_wrapper(List x) {
  return IpAddressVector(x).encodeStrings();
}

// [[Rcpp::export]]
List parse_network_wrapper(CharacterVector x, LogicalVector strict) {
  if (strict.size() != 1) {
    stop("argument 'strict' must be a scalar logical value");
  }
  return IpNetworkVector(x, strict[0]).encodeR();
}

// [[Rcpp::export]]
CharacterVector print_network_wrapper(List x) {
  return IpNetworkVector(x).encodeStrings();
}

/*-----------------------
 *  Comparison operators
 * ----------------------
 */
// [[Rcpp::export]]
DataFrame compare_address_wrapper(List x) {
  return IpAddressVector(x).encodeComparable();
}

// [[Rcpp::export]]
DataFrame compare_network_wrapper(List x) {
  IpAddressVector address(List::create(
      _["address1"] = x["address1"],
      _["address2"] = x["address2"],
      _["address3"] = x["address3"],
      _["address4"] = x["address4"],
      _["is_ipv6"] = x["is_ipv6"]
  ));
  return address.encodeComparable();
}

/*--------------
 *  Bit masking
 * -------------
 */
// [[Rcpp::export]]
List netmask_wrapper(List x) {
  return IpAddressVector::createNetmask(x["is_ipv6"], x["prefix"]).encodeR();
}

// [[Rcpp::export]]
List hostmask_wrapper(List x) {
  return IpAddressVector::createHostmask(x["is_ipv6"], x["prefix"]).encodeR();
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
