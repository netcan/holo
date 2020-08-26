//
// Created by Darwin Yuan on 2020/8/18.
//

#ifndef GRAPH_FILTER_H
#define GRAPH_FILTER_H

#include <holo/holo_ns.h>
#include <holo/types/type_c.h>
#include <type_traits>

HOLO_NS_BEGIN

namespace detail {
   template<typename PRED, typename RESULT, typename = void, typename ... Ts>
   struct filter_impl {
      using type = RESULT;
   };

   template<typename PRED, typename RESULT, typename H, typename ... Ts>
   struct filter_impl<PRED, RESULT, std::enable_if_t<Is_Pred_Satisfied<PRED, H>>, H, Ts...> {
      using type = typename filter_impl<PRED, typename RESULT::template append_type<H>, void, Ts...>::type;
   };

   template<typename PRED, typename RESULT, typename H, typename ... Ts>
   struct filter_impl<PRED, RESULT, std::enable_if_t<!Is_Pred_Satisfied <PRED, H>>, H, Ts...> {
      using type = typename filter_impl<PRED, RESULT, void, Ts...>::type;
   };
}

template <typename ... Ts, typename F>
constexpr auto filter(F&& f, const tuple<Ts...>&) {
   return typename detail::filter_impl<F, tuple<>, void, Ts...>::type{};
}

HOLO_NS_END

#endif //GRAPH_FILTER_H
