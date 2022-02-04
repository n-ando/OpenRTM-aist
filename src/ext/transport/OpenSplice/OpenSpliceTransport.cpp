// -*- C++ -*-
/*!
 * @file  OpenSpliceOutPort.cpp
 * @brief OpenSpliceOutPort class
 * @date  $Date: 2019-01-31 03:08:03 $
 * @author Nobuhiko Miyamoto <n-miyamoto@aist.go.jp>
 *
 * Copyright (C) 2019
 *     Nobuhiko Miyamoto
 *     Robot Innovation Research Center,
 *     National Institute of
 *         Advanced Industrial Science and Technology (AIST), Japan
 *
 *     All rights reserved.
 *
 *
 */


#include <coil/Factory.h>
#include "OpenSpliceTransport.h"
#include "OpenSpliceOutPort.h"
#include "OpenSpliceInPort.h"
#include "OpenSpliceMessageInfo.h"
#include "OpenSpliceManagerFunc.h"


static const char* const opensplice_sub_option[] =
{
  "reader.durability.kind.__value__", "TRANSIENT_DURABILITY_QOS",
  "reader.durability.kind.__widget__", "radio",
  "reader.durability.kind.__constraint__", "(VOLATILE_DURABILITY_QOS, TRANSIENT_LOCAL_DURABILITY_QOS, TRANSIENT_DURABILITY_QOS, PERSISTENT_DURABILITY_QOS)",
  "reader.deadline.period.sec.__value__", "2147483647",
  "reader.deadline.period.sec.__widget__", "spin",
  "reader.deadline.period.sec.__constraint__", "0 <= x <= 2147483647",
  "reader.deadline.period.nanosec.__value__", "2147483647",
  "reader.deadline.period.nanosec.__widget__", "text",
  "reader.deadline.period.nanosec.__constraint__", "0 <= x <= 2147483647",
  "reader.latency_budget.duration.sec.__value__", "0",
  "reader.latency_budget.duration.sec.__widget__", "spin",
  "reader.latency_budget.duration.sec.__constraint__", "0 <= x <= 2147483647",
  "reader.latency_budget.duration.nanosec.__value__", "0",
  "reader.latency_budget.duration.nanosec.__widget__", "spin",
  "reader.latency_budget.duration.nanosec.__constraint__", "0 <= x <= 2147483647",
  "reader.liveliness.kind.__value__", "AUTOMATIC_LIVELINESS_QOS",
  "reader.liveliness.kind.__widget__", "radio",
  "reader.liveliness.kind.__constraint__", "(AUTOMATIC_LIVELINESS_QOS, MANUAL_BY_PARTICIPANT_LIVELINESS_QOS, MANUAL_BY_TOPIC_LIVELINESS_QOS)",
  "reader.reliability.kind.__value__", "BEST_EFFORT_RELIABILITY_QOS",
  "reader.reliability.kind.__widget__", "radio",
  "reader.reliability.kind.__constraint__", "(BEST_EFFORT_RELIABILITY_QOS, RELIABLE_RELIABILITY_QOS)",
  "reader.reliability.max_blocking_time.sec.__value__", "2147483647",
  "reader.reliability.max_blocking_time.sec.__widget__", "spin",
  "reader.reliability.max_blocking_time.sec.__constraint__", "0 <= x <= 2147483647",
  "reader.reliability.max_blocking_time.nanosec.__value__", "2147483647",
  "reader.reliability.max_blocking_time.nanosec.__widget__", "spin",
  "reader.reliability.max_blocking_time.nanosec.__constraint__", "0 <= x <= 2147483647",
  "reader.reliability.synchronous.__value__", "NO",
  "reader.reliability.synchronous.__widget__", "radio",
  "reader.reliability.synchronous.__constraint__", "(YES, NO)",
  "reader.destination_order.kind.__value__", "BY_RECEPTION_TIMESTAMP_DESTINATIONORDER_QOS",
  "reader.destination_order.kind.__widget__", "radio",
  "reader.destination_order.kind.__constraint__", "(BY_RECEPTION_TIMESTAMP_DESTINATIONORDER_QOS, BY_SOURCE_TIMESTAMP_DESTINATIONORDER_QOS)",
  "reader.history.kind.__value__", "KEEP_LAST_HISTORY_QOS",
  "reader.history.kind.__widget__", "radio",
  "reader.history.kind.__constraint__", "(KEEP_LAST_HISTORY_QOS, KEEP_ALL_HISTORY_QOS)",
  "reader.history.depth.__value__", "1",
  "reader.history.depth.__widget__", "spin",
  "reader.history.depth.__constraint__", "0 <= x <= 2147483647",
  "reader.resource_limits.max_samples.__value__", "-1",
  "reader.resource_limits.max_samples.__widget__", "spin",
  "reader.resource_limits.max_samples.__constraint__", "-1 <= x <= 2147483647",
  "reader.resource_limits.max_instances.__value__", "-1",
  "reader.resource_limits.max_instances.__widget__", "spin",
  "reader.resource_limits.max_instances.__constraint__", "-1 <= x <= 2147483647",
  "reader.resource_limits.max_samples_per_instance.__value__", "-1",
  "reader.resource_limits.max_samples_per_instance.__widget__", "spin",
  "reader.resource_limits.max_samples_per_instance.__constraint__", "-1 <= x <= 2147483647",
  "reader.ownership.kind.__value__", "SHARED_OWNERSHIP_QOS",
  "reader.ownership.kind.__widget__", "radio",
  "reader.ownership.kind.__constraint__", "(SHARED_OWNERSHIP_QOS, EXCLUSIVE_OWNERSHIP_QOS)",
  "reader.time_based_filter.minimum_separation.sec.__value__", "0",
  "reader.time_based_filter.minimum_separation.sec.__widget__", "spin",
  "reader.time_based_filter.minimum_separation.sec.__constraint__", "0 <= x <= 2147483647",
  "reader.time_based_filter.minimum_separation.nanosec.__value__", "0",
  "reader.time_based_filter.minimum_separation.nanosec.__widget__", "spin",
  "reader.time_based_filter.minimum_separation.nanosec.__constraint__", "0 <= x <= 2147483647",
  "reader.reader_data_lifecycle.autopurge_disposed_samples_delay.sec.__value__", "2147483647",
  "reader.reader_data_lifecycle.autopurge_disposed_samples_delay.sec.__widget__", "spin",
  "reader.reader_data_lifecycle.autopurge_disposed_samples_delay.sec.__constraint__", "0 <= x <= 2147483647",
  "reader.reader_data_lifecycle.autopurge_disposed_samples_delay.nanosec.__value__", "2147483647",
  "reader.reader_data_lifecycle.autopurge_disposed_samples_delay.nanosec.__widget__", "spin",
  "reader.reader_data_lifecycle.autopurge_disposed_samples_delay.nanosec.__constraint__", "0 <= x <= 2147483647",
  "reader.reader_data_lifecycle.autopurge_dispose_all.__value__", "NO",
  "reader.reader_data_lifecycle.autopurge_dispose_all.__widget__", "radio",
  "reader.reader_data_lifecycle.autopurge_dispose_all.__constraint__", "(YES, NO)",
  "reader.reader_data_lifecycle.autopurge_nowriter_samples_delay.sec.__value__", "2147483647",
  "reader.reader_data_lifecycle.autopurge_nowriter_samples_delay.sec.__widget__", "spin",
  "reader.reader_data_lifecycle.autopurge_nowriter_samples_delay.sec.__constraint__", "0 <= x <= 2147483647",
  "reader.reader_data_lifecycle.autopurge_nowriter_samples_delay.nanosec.__value__", "2147483647",
  "reader.reader_data_lifecycle.autopurge_nowriter_samples_delay.nanosec.__widget__", "spin",
  "reader.reader_data_lifecycle.autopurge_nowriter_samples_delay.nanosec.__constraint__", "0 <= x <= 2147483647",
  "reader.reader_data_lifecycle.enable_invalid_samples.__value__", "YES",
  "reader.reader_data_lifecycle.enable_invalid_samples.__widget__", "radio",
  "reader.reader_data_lifecycle.enable_invalid_samples.__constraint__", "(YES, NO)",
  "reader.reader_data_lifecycle.invalid_sample_visibility.kind.__value__", "MINIMUM_INVALID_SAMPLES",
  "reader.reader_data_lifecycle.invalid_sample_visibility.kind.__widget__", "radio",
  "reader.reader_data_lifecycle.invalid_sample_visibility.kind.__constraint__", "(NO_INVALID_SAMPLES, MINIMUM_INVALID_SAMPLES, ALL_INVALID_SAMPLES)",
  "topic.durability.kind.__value__", "TRANSIENT_DURABILITY_QOS",
  "topic.durability.kind.__widget__", "radio",
  "topic.durability.kind.__constraint__", "(VOLATILE_DURABILITY_QOS, TRANSIENT_LOCAL_DURABILITY_QOS, TRANSIENT_DURABILITY_QOS, PERSISTENT_DURABILITY_QOS)",
  "topic.deadline.period.sec.__value__", "2147483647",
  "topic.deadline.period.sec.__widget__", "spin",
  "topic.deadline.period.sec.__constraint__", "0 <= x <= 2147483647",
  "topic.deadline.period.nanosec.__value__", "2147483647",
  "topic.deadline.period.nanosec.__widget__", "spin",
  "topic.deadline.period.nanosec.__constraint__", "0 <= x <= 2147483647",
  "topic.latency_budget.duration.sec.__value__", "0",
  "topic.latency_budget.duration.sec.__widget__", "spin",
  "topic.latency_budget.duration.sec.__constraint__", "0 <= x <= 2147483647",
  "topic.latency_budget.duration.nanosec.__value__", "0",
  "topic.latency_budget.duration.nanosec.__widget__", "spin",
  "topic.latency_budget.duration.nanosec.__constraint__", "0 <= x <= 2147483647",
  "topic.liveliness.kind.__value__", "AUTOMATIC_LIVELINESS_QOS",
  "topic.liveliness.kind.__widget__", "radio",
  "topic.liveliness.kind.__constraint__", "(AUTOMATIC_LIVELINESS_QOS, MANUAL_BY_PARTICIPANT_LIVELINESS_QOS, MANUAL_BY_TOPIC_LIVELINESS_QOS)",
  "topic.reliability.kind.__value__", "RELIABLE_RELIABILITY_QOS",
  "topic.reliability.kind.__widget__", "radio",
  "topic.reliability.kind.__constraint__", "(BEST_EFFORT_RELIABILITY_QOS, RELIABLE_RELIABILITY_QOS)",
  "topic.reliability.max_blocking_time.sec.__value__", "2147483647",
  "topic.reliability.max_blocking_time.sec.__widget__", "spin",
  "topic.reliability.max_blocking_time.sec.__constraint__", "0 <= x <= 2147483647",
  "topic.reliability.max_blocking_time.nanosec.__value__", "2147483647",
  "topic.reliability.max_blocking_time.nanosec.__widget__", "spin",
  "topic.reliability.max_blocking_time.nanosec.__constraint__", "0 <= x <= 2147483647",
  "topic.reliability.synchronous.__value__", "NO",
  "topic.reliability.synchronous.__widget__", "radio",
  "topic.reliability.synchronous.__constraint__", "(YES, NO)",
  "topic.destination_order.kind.__value__", "BY_RECEPTION_TIMESTAMP_DESTINATIONORDER_QOS",
  "topic.destination_order.kind.__widget__", "radio",
  "topic.destination_order.kind.__constraint__", "(BY_RECEPTION_TIMESTAMP_DESTINATIONORDER_QOS, BY_SOURCE_TIMESTAMP_DESTINATIONORDER_QOS)",
  "topic.history.kind.__value__", "KEEP_ALL_HISTORY_QOS",
  "topic.history.kind.__widget__", "radio",
  "topic.history.kind.__constraint__", "(KEEP_LAST_HISTORY_QOS, KEEP_ALL_HISTORY_QOS)",
  "topic.history.depth.__value__", "1",
  "topic.history.depth.__widget__", "spin",
  "topic.history.depth.__constraint__", "0 <= x <= 2147483647",
  "topic.resource_limits.max_samples.__value__", "-1",
  "topic.resource_limits.max_samples.__widget__", "spin",
  "topic.resource_limits.max_samples.__constraint__", "-1 <= x <= 2147483647",
  "topic.resource_limits.max_instances.__value__", "-1",
  "topic.resource_limits.max_instances.__widget__", "spin",
  "topic.resource_limits.max_instances.__constraint__", "-1 <= x <= 2147483647",
  "topic.resource_limits.max_samples_per_instance.__value__", "-1",
  "topic.resource_limits.max_samples_per_instance.__widget__", "spin",
  "topic.resource_limits.max_samples_per_instance.__constraint__", "-1 <= x <= 2147483647",
  "topic.transport_priority.value.__value__", "0",
  "topic.transport_priority.value.__widget__", "spin",
  "topic.transport_priority.value.__constraint__", "0 <= x <= 2147483647",
  "topic.lifespan.duration.sec.__value__", "2147483647",
  "topic.lifespan.duration.sec.__widget__", "spin",
  "topic.lifespan.duration.sec.__constraint__", "0 <= x <= 2147483647",
  "topic.lifespan.duration.nanosec.__value__", "2147483647",
  "topic.lifespan.duration.nanosec.__widget__", "spin",
  "topic.lifespan.duration.nanosec.__constraint__", "0 <= x <= 2147483647",
  "topic.ownership.kind.__value__", "SHARED_OWNERSHIP_QOS",
  "topic.ownership.kind.__widget__", "radio",
  "topic.ownership.kind.__constraint__", "(SHARED_OWNERSHIP_QOS, EXCLUSIVE_OWNERSHIP_QOS)",
  "topic.transport_priority.value.__value__", "0",
  "topic.transport_priority.value.__widget__", "spin",
  "topic.transport_priority.value.__constraint__", "0 <= x <= 2147483647",
  "topic.durability_service.history_depth.__value__", "1",
  "topic.durability_service.history_depth.__widget__", "spin",
  "topic.durability_service.history_depth.__constraint__", "0 <= x <= 2147483647",
  "topic.durability_service.history_kind.__value__", "KEEP_LAST_HISTORY_QOS",
  "topic.durability_service.history_kind.__widget__", "radio",
  "topic.durability_service.history_kind.__constraint__", "(KEEP_LAST_HISTORY_QOS, KEEP_ALL_HISTORY_QOS)",
  "topic.durability_service.max_instances.__value__", "-1",
  "topic.durability_service.max_instances.__widget__", "spin",
  "topic.durability_service.max_instances.__constraint__", "-1 <= x <= 2147483647",
  "topic.durability_service.max_samples.__value__", "-1",
  "topic.durability_service.max_samples.__widget__", "spin",
  "topic.durability_service.max_samples.__constraint__", "-1 <= x <= 2147483647",
  "topic.durability_service.max_samples_per_instance.__value__", "-1",
  "topic.durability_service.max_samples_per_instance.__widget__", "spin",
  "topic.durability_service.max_samples_per_instance.__constraint__", "-1 <= x <= 2147483647",
  "topic.durability_service.service_cleanup_delay.sec.__value__", "0",
  "topic.durability_service.service_cleanup_delay.sec.__widget__", "spin",
  "topic.durability_service.service_cleanup_delay.sec.__constraint__", "0 <= x <= 2147483647",
  "topic.durability_service.service_cleanup_delay.nanosec.__value__", "0",
  "topic.durability_service.service_cleanup_delay.nanosec.__widget__", "spin",
  "topic.durability_service.service_cleanup_delay.nanosec.__constraint__", "0 <= x <= 2147483647",
  ""
};

static const char* const opensplice_pub_option[] =
{
  "writer.durability.kind.__value__", "TRANSIENT_DURABILITY_QOS",
  "writer.durability.kind.__widget__", "radio",
  "writer.durability.kind.__constraint__", "(VOLATILE_DURABILITY_QOS, TRANSIENT_LOCAL_DURABILITY_QOS, TRANSIENT_DURABILITY_QOS, PERSISTENT_DURABILITY_QOS)",
  "writer.deadline.period.sec.__value__", "2147483647",
  "writer.deadline.period.sec.__widget__", "spin",
  "writer.deadline.period.sec.__constraint__", "0 <= x <= 2147483647",
  "writer.deadline.period.nanosec.__value__", "2147483647",
  "writer.deadline.period.nanosec.__widget__", "text",
  "writer.deadline.period.nanosec.__constraint__", "0 <= x <= 2147483647",
  "writer.latency_budget.duration.sec.__value__", "0",
  "writer.latency_budget.duration.sec.__widget__", "spin",
  "writer.latency_budget.duration.sec.__constraint__", "0 <= x <= 2147483647",
  "writer.latency_budget.duration.nanosec.__value__", "0",
  "writer.latency_budget.duration.nanosec.__widget__", "spin",
  "writer.latency_budget.duration.nanosec.__constraint__", "0 <= x <= 2147483647",
  "writer.liveliness.kind.__value__", "AUTOMATIC_LIVELINESS_QOS",
  "writer.liveliness.kind.__widget__", "radio",
  "writer.liveliness.kind.__constraint__", "(AUTOMATIC_LIVELINESS_QOS, MANUAL_BY_PARTICIPANT_LIVELINESS_QOS, MANUAL_BY_TOPIC_LIVELINESS_QOS)",
  "writer.reliability.kind.__value__", "RELIABLE_RELIABILITY_QOS",
  "writer.reliability.kind.__widget__", "radio",
  "writer.reliability.kind.__constraint__", "(BEST_EFFORT_RELIABILITY_QOS, RELIABLE_RELIABILITY_QOS)",
  "writer.reliability.max_blocking_time.sec.__value__", "2147483647",
  "writer.reliability.max_blocking_time.sec.__widget__", "spin",
  "writer.reliability.max_blocking_time.sec.__constraint__", "0 <= x <= 2147483647",
  "writer.reliability.max_blocking_time.nanosec.__value__", "2147483647",
  "writer.reliability.max_blocking_time.nanosec.__widget__", "spin",
  "writer.reliability.max_blocking_time.nanosec.__constraint__", "0 <= x <= 2147483647",
  "writer.reliability.synchronous.__value__", "NO",
  "writer.reliability.synchronous.__widget__", "radio",
  "writer.reliability.synchronous.__constraint__", "(YES, NO)",
  "writer.destination_order.kind.__value__", "BY_RECEPTION_TIMESTAMP_DESTINATIONORDER_QOS",
  "writer.destination_order.kind.__widget__", "radio",
  "writer.destination_order.kind.__constraint__", "(BY_RECEPTION_TIMESTAMP_DESTINATIONORDER_QOS, BY_SOURCE_TIMESTAMP_DESTINATIONORDER_QOS)",
  "writer.history.kind.__value__", "KEEP_LAST_HISTORY_QOS",
  "writer.history.kind.__widget__", "radio",
  "writer.history.kind.__constraint__", "(KEEP_LAST_HISTORY_QOS, KEEP_ALL_HISTORY_QOS)",
  "writer.history.depth.__value__", "1",
  "writer.history.depth.__widget__", "spin",
  "writer.history.depth.__constraint__", "0 <= x <= 2147483647",
  "writer.resource_limits.max_samples.__value__", "-1",
  "writer.resource_limits.max_samples.__widget__", "spin",
  "writer.resource_limits.max_samples.__constraint__", "-1 <= x <= 2147483647",
  "writer.resource_limits.max_instances.__value__", "-1",
  "writer.resource_limits.max_instances.__widget__", "spin",
  "writer.resource_limits.max_instances.__constraint__", "-1 <= x <= 2147483647",
  "writer.resource_limits.max_samples_per_instance.__value__", "-1",
  "writer.resource_limits.max_samples_per_instance.__widget__", "spin",
  "writer.resource_limits.max_samples_per_instance.__constraint__", "-1 <= x <= 2147483647",
  "writer.transport_priority.value.__value__", "0",
  "writer.transport_priority.value.__widget__", "spin",
  "writer.transport_priority.value.__constraint__", "0 <= x <= 2147483647",
  "writer.lifespan.duration.sec.__value__", "2147483647",
  "writer.lifespan.duration.sec.__widget__", "spin",
  "writer.lifespan.duration.sec.__constraint__", "0 <= x <= 2147483647",
  "writer.lifespan.duration.nanosec.__value__", "2147483647",
  "writer.lifespan.duration.nanosec.__widget__", "spin",
  "writer.lifespan.duration.nanosec.__constraint__", "0 <= x <= 2147483647",
  "writer.ownership.kind.__value__", "SHARED_OWNERSHIP_QOS",
  "writer.ownership.kind.__widget__", "radio",
  "writer.ownership.kind.__constraint__", "(SHARED_OWNERSHIP_QOS, EXCLUSIVE_OWNERSHIP_QOS)",
  "writer.ownership_strength.value.__value__", "0",
  "writer.ownership_strength.value.__widget__", "spin",
  "writer.ownership_strength.value.__constraint__", "0 <= x <= 2147483647",
  "writer.writer_data_lifecycle.autodispose_unregistered_instances.__value__", "YES",
  "writer.writer_data_lifecycle.autodispose_unregistered_instances.__widget__", "radio",
  "writer.writer_data_lifecycle.autodispose_unregistered_instances.__constraint__", "(YES, NO)",
  "writer.writer_data_lifecycle.autopurge_suspended_samples_delay.sec.__value__", "2147483647",
  "writer.writer_data_lifecycle.autopurge_suspended_samples_delay.sec.__widget__", "spin",
  "writer.writer_data_lifecycle.autopurge_suspended_samples_delay.sec.__constraint__", "0 <= x <= 2147483647",
  "writer.writer_data_lifecycle.autopurge_suspended_samples_delay.nanosec.__value__", "2147483647",
  "writer.writer_data_lifecycle.autopurge_suspended_samples_delay.nanosec.__widget__", "spin",
  "writer.writer_data_lifecycle.autopurge_suspended_samples_delay.nanosec.__constraint__", "0 <= x <= 2147483647",
  "writer.writer_data_lifecycle.autounregister_instance_dela.sec.__value__", "2147483647",
  "writer.writer_data_lifecycle.autounregister_instance_dela.sec.__widget__", "spin",
  "writer.writer_data_lifecycle.autounregister_instance_dela.sec.__constraint__", "0 <= x <= 2147483647",
  "writer.writer_data_lifecycle.autounregister_instance_dela.nanosec.__value__", "2147483647",
  "writer.writer_data_lifecycle.autounregister_instance_dela.nanosec.__widget__", "spin",
  "writer.writer_data_lifecycle.autounregister_instance_dela.nanosec.__constraint__", "0 <= x <= 2147483647",
  "topic.durability.kind.__value__", "TRANSIENT_DURABILITY_QOS",
  "topic.durability.kind.__widget__", "radio",
  "topic.durability.kind.__constraint__", "(VOLATILE_DURABILITY_QOS, TRANSIENT_LOCAL_DURABILITY_QOS, TRANSIENT_DURABILITY_QOS, PERSISTENT_DURABILITY_QOS)",
  "topic.deadline.period.sec.__value__", "2147483647",
  "topic.deadline.period.sec.__widget__", "spin",
  "topic.deadline.period.sec.__constraint__", "0 <= x <= 2147483647",
  "topic.deadline.period.nanosec.__value__", "2147483647",
  "topic.deadline.period.nanosec.__widget__", "spin",
  "topic.deadline.period.nanosec.__constraint__", "0 <= x <= 2147483647",
  "topic.latency_budget.duration.sec.__value__", "0",
  "topic.latency_budget.duration.sec.__widget__", "spin",
  "topic.latency_budget.duration.sec.__constraint__", "0 <= x <= 2147483647",
  "topic.latency_budget.duration.nanosec.__value__", "0",
  "topic.latency_budget.duration.nanosec.__widget__", "spin",
  "topic.latency_budget.duration.nanosec.__constraint__", "0 <= x <= 2147483647",
  "topic.liveliness.kind.__value__", "AUTOMATIC_LIVELINESS_QOS",
  "topic.liveliness.kind.__widget__", "radio",
  "topic.liveliness.kind.__constraint__", "(AUTOMATIC_LIVELINESS_QOS, MANUAL_BY_PARTICIPANT_LIVELINESS_QOS, MANUAL_BY_TOPIC_LIVELINESS_QOS)",
  "topic.reliability.kind.__value__", "RELIABLE_RELIABILITY_QOS",
  "topic.reliability.kind.__widget__", "radio",
  "topic.reliability.kind.__constraint__", "(BEST_EFFORT_RELIABILITY_QOS, RELIABLE_RELIABILITY_QOS)",
  "topic.reliability.max_blocking_time.sec.__value__", "2147483647",
  "topic.reliability.max_blocking_time.sec.__widget__", "spin",
  "topic.reliability.max_blocking_time.sec.__constraint__", "0 <= x <= 2147483647",
  "topic.reliability.max_blocking_time.nanosec.__value__", "2147483647",
  "topic.reliability.max_blocking_time.nanosec.__widget__", "spin",
  "topic.reliability.max_blocking_time.nanosec.__constraint__", "0 <= x <= 2147483647",
  "topic.reliability.synchronous.__value__", "NO",
  "topic.reliability.synchronous.__widget__", "radio",
  "topic.reliability.synchronous.__constraint__", "(YES, NO)",
  "topic.destination_order.kind.__value__", "BY_RECEPTION_TIMESTAMP_DESTINATIONORDER_QOS",
  "topic.destination_order.kind.__widget__", "radio",
  "topic.destination_order.kind.__constraint__", "(BY_RECEPTION_TIMESTAMP_DESTINATIONORDER_QOS, BY_SOURCE_TIMESTAMP_DESTINATIONORDER_QOS)",
  "topic.history.kind.__value__", "KEEP_ALL_HISTORY_QOS",
  "topic.history.kind.__widget__", "radio",
  "topic.history.kind.__constraint__", "(KEEP_LAST_HISTORY_QOS, KEEP_ALL_HISTORY_QOS)",
  "topic.history.depth.__value__", "1",
  "topic.history.depth.__widget__", "spin",
  "topic.history.depth.__constraint__", "0 <= x <= 2147483647",
  "topic.resource_limits.max_samples.__value__", "-1",
  "topic.resource_limits.max_samples.__widget__", "spin",
  "topic.resource_limits.max_samples.__constraint__", "-1 <= x <= 2147483647",
  "topic.resource_limits.max_instances.__value__", "-1",
  "topic.resource_limits.max_instances.__widget__", "spin",
  "topic.resource_limits.max_instances.__constraint__", "-1 <= x <= 2147483647",
  "topic.resource_limits.max_samples_per_instance.__value__", "-1",
  "topic.resource_limits.max_samples_per_instance.__widget__", "spin",
  "topic.resource_limits.max_samples_per_instance.__constraint__", "-1 <= x <= 2147483647",
  "topic.transport_priority.value.__value__", "0",
  "topic.transport_priority.value.__widget__", "spin",
  "topic.transport_priority.value.__constraint__", "0 <= x <= 2147483647",
  "topic.lifespan.duration.sec.__value__", "2147483647",
  "topic.lifespan.duration.sec.__widget__", "spin",
  "topic.lifespan.duration.sec.__constraint__", "0 <= x <= 2147483647",
  "topic.lifespan.duration.nanosec.__value__", "2147483647",
  "topic.lifespan.duration.nanosec.__widget__", "spin",
  "topic.lifespan.duration.nanosec.__constraint__", "0 <= x <= 2147483647",
  "topic.ownership.kind.__value__", "SHARED_OWNERSHIP_QOS",
  "topic.ownership.kind.__widget__", "radio",
  "topic.ownership.kind.__constraint__", "(SHARED_OWNERSHIP_QOS, EXCLUSIVE_OWNERSHIP_QOS)",
  "topic.transport_priority.value.__value__", "0",
  "topic.transport_priority.value.__widget__", "spin",
  "topic.transport_priority.value.__constraint__", "0 <= x <= 2147483647",
  "topic.durability_service.history_depth.__value__", "1",
  "topic.durability_service.history_depth.__widget__", "spin",
  "topic.durability_service.history_depth.__constraint__", "0 <= x <= 2147483647",
  "topic.durability_service.history_kind.__value__", "KEEP_LAST_HISTORY_QOS",
  "topic.durability_service.history_kind.__widget__", "radio",
  "topic.durability_service.history_kind.__constraint__", "(KEEP_LAST_HISTORY_QOS, KEEP_ALL_HISTORY_QOS)",
  "topic.durability_service.max_instances.__value__", "-1",
  "topic.durability_service.max_instances.__widget__", "spin",
  "topic.durability_service.max_instances.__constraint__", "-1 <= x <= 2147483647",
  "topic.durability_service.max_samples.__value__", "-1",
  "topic.durability_service.max_samples.__widget__", "spin",
  "topic.durability_service.max_samples.__constraint__", "-1 <= x <= 2147483647",
  "topic.durability_service.max_samples_per_instance.__value__", "-1",
  "topic.durability_service.max_samples_per_instance.__widget__", "spin",
  "topic.durability_service.max_samples_per_instance.__constraint__", "-1 <= x <= 2147483647",
  "topic.durability_service.service_cleanup_delay.sec.__value__", "0",
  "topic.durability_service.service_cleanup_delay.sec.__widget__", "spin",
  "topic.durability_service.service_cleanup_delay.sec.__constraint__", "0 <= x <= 2147483647",
  "topic.durability_service.service_cleanup_delay.nanosec.__value__", "0",
  "topic.durability_service.service_cleanup_delay.nanosec.__widget__", "spin",
  "topic.durability_service.service_cleanup_delay.nanosec.__constraint__", "0 <= x <= 2147483647",
  ""
};


ManagerActionListener::ManagerActionListener()
{

}
ManagerActionListener::~ManagerActionListener()
{

}
void ManagerActionListener::preShutdown()
{

}
void ManagerActionListener::postShutdown()
{
    //終了処理をすると異常終了するため一旦コメントアウトする
    //RTC_OpenSplice::shutdown();
}
void ManagerActionListener::postReinit()
{

}

void ManagerActionListener::preReinit()
{

}



extern "C"
{
  /*!
   * @if jp
   * @brief モジュール初期化関数
   * @else
   * @brief Module initialization
   * @endif
   */
  void OpenSpliceTransportInit(RTC::Manager* manager)
  {
      {
          coil::Properties prop(opensplice_sub_option);
          RTC::InPortConsumerFactory& factory(RTC::InPortConsumerFactory::instance());
          factory.addFactory("opensplice",
              ::coil::Creator< ::RTC::InPortConsumer,
              ::RTC::OpenSpliceOutPort>,
              ::coil::Destructor< ::RTC::InPortConsumer,
              ::RTC::OpenSpliceOutPort>,
              prop);
      }
      {
          coil::Properties prop(opensplice_pub_option);
          RTC::InPortProviderFactory& factory(RTC::InPortProviderFactory::instance());
          factory.addFactory("opensplice",
              ::coil::Creator< ::RTC::InPortProvider,
              ::RTC::OpenSpliceInPort>,
              ::coil::Destructor< ::RTC::InPortProvider,
              ::RTC::OpenSpliceInPort>,
              prop);
      }
      
      
      RTC_OpenSplice::start(manager->getConfig().getNode("opensplice"));
      OpenSpliceMessageInfoInit(manager->getConfig().getNode("opensplice"));
    
      ManagerActionListener *listener = new ManagerActionListener();
      manager->addManagerActionListener(listener);
      

  }
  
};


