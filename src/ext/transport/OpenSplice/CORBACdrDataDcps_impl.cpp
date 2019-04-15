#include "CORBACdrDataDcps_impl.h"
#include "CORBACdrDataSplDcps.h"
#include <iostream>
//


// DDS OpenRTM::CORBACdrData TypeSupportMetaHolder Object Body
OpenRTM::CORBACdrDataTypeSupportMetaHolder::CORBACdrDataTypeSupportMetaHolder (::DDS::String datatype, ::DDS::String keys, ::DDS::String descriptor) :
        DDS::OpenSplice::TypeSupportMetaHolder (datatype, "", keys),
        m_datatype(DDS::string_dup(datatype)), m_keys(DDS::string_dup(keys)), m_descriptor(DDS::string_dup(descriptor))
{
    copyIn = (DDS::OpenSplice::cxxCopyIn) OpenSplice_OpenRTM_CORBACdrData_copyIn;
    copyOut = (DDS::OpenSplice::cxxCopyOut) OpenSplice_OpenRTM_CORBACdrData_copyOut;
    
    metaDescriptorArrLength = 1;
    metaDescriptorLength = strlen(m_descriptor)+1;
    metaDescriptor = new const char*[metaDescriptorArrLength];
    metaDescriptor[0] = DDS::string_dup(m_descriptor);
}

OpenRTM::CORBACdrDataTypeSupportMetaHolder::~CORBACdrDataTypeSupportMetaHolder ()
{
    // Rely on parent destructor.
}

::DDS::OpenSplice::TypeSupportMetaHolder *
OpenRTM::CORBACdrDataTypeSupportMetaHolder::clone()
{
    return new OpenRTM::CORBACdrDataTypeSupportMetaHolder(m_datatype, m_keys, m_descriptor);
}

::DDS::OpenSplice::DataWriter *
OpenRTM::CORBACdrDataTypeSupportMetaHolder::create_datawriter ()
{
    return new OpenRTM::CORBACdrDataDataWriter_impl();
}

::DDS::OpenSplice::DataReader *
OpenRTM::CORBACdrDataTypeSupportMetaHolder::create_datareader ()
{
    return new OpenRTM::CORBACdrDataDataReader_impl();
}

::DDS::OpenSplice::DataReaderView *
OpenRTM::CORBACdrDataTypeSupportMetaHolder::create_view ()
{
    return new OpenRTM::CORBACdrDataDataReaderView_impl();
}

// DDS OpenRTM::CORBACdrData TypeSupport Object Body
OpenRTM::CORBACdrDataTypeSupport::CORBACdrDataTypeSupport (::DDS::String datatype, ::DDS::String keys, ::DDS::String descriptor) :
        DDS::OpenSplice::TypeSupport()
{
    tsMetaHolder = new OpenRTM::CORBACdrDataTypeSupportMetaHolder(datatype, keys, descriptor);
    
}

OpenRTM::CORBACdrDataTypeSupport::~CORBACdrDataTypeSupport ()
{
    DDS::release(tsMetaHolder);
}

// DDS OpenRTM::CORBACdrData DataWriter_impl Object Body
OpenRTM::CORBACdrDataDataWriter_impl::CORBACdrDataDataWriter_impl ()
{
    // Parent constructor takes care of everything.
}

OpenRTM::CORBACdrDataDataWriter_impl::~CORBACdrDataDataWriter_impl ()
{
    // Parent destructor takes care of everything.
}

::DDS::ReturnCode_t
OpenRTM::CORBACdrDataDataWriter_impl::init (
        DDS::OpenSplice::Publisher *publisher,
        DDS::OpenSplice::DomainParticipant *participant,
        const DDS::DataWriterQos &qos,
        DDS::OpenSplice::Topic *a_topic,
        const char *name,
        DDS::OpenSplice::cxxCopyIn copyIn,
        DDS::OpenSplice::cxxCopyOut copyOut,
        u_writerCopy writerCopy,
        void *cdrMarshaler)
{
    return DDS::OpenSplice::FooDataWriter_impl::nlReq_init(
            publisher, participant, qos, a_topic, name, copyIn, copyOut, writerCopy, cdrMarshaler);
}

::DDS::InstanceHandle_t
OpenRTM::CORBACdrDataDataWriter_impl::register_instance (
    const OpenRTM::CORBACdrData & instance_data) THROW_ORB_EXCEPTIONS
{
    return DDS::OpenSplice::FooDataWriter_impl::register_instance(&instance_data);
}

::DDS::InstanceHandle_t
OpenRTM::CORBACdrDataDataWriter_impl::register_instance_w_timestamp (
    const CORBACdrData & instance_data,
    const ::DDS::Time_t & source_timestamp) THROW_ORB_EXCEPTIONS
{
    return DDS::OpenSplice::FooDataWriter_impl::register_instance_w_timestamp(&instance_data, source_timestamp);
}

::DDS::ReturnCode_t
OpenRTM::CORBACdrDataDataWriter_impl::unregister_instance (
    const OpenRTM::CORBACdrData & instance_data,
    ::DDS::InstanceHandle_t handle) THROW_ORB_EXCEPTIONS
{
    return DDS::OpenSplice::FooDataWriter_impl::unregister_instance(&instance_data, handle);
}

::DDS::ReturnCode_t
OpenRTM::CORBACdrDataDataWriter_impl::unregister_instance_w_timestamp (
    const CORBACdrData & instance_data,
    ::DDS::InstanceHandle_t handle,
    const ::DDS::Time_t & source_timestamp) THROW_ORB_EXCEPTIONS
{
    return DDS::OpenSplice::FooDataWriter_impl::unregister_instance_w_timestamp(&instance_data, handle, source_timestamp);
}

::DDS::ReturnCode_t
OpenRTM::CORBACdrDataDataWriter_impl::write_cdr(
    const ::DDS::CDRSample & data,
    ::DDS::InstanceHandle_t handle) THROW_ORB_EXCEPTIONS
{
    return DDS::OpenSplice::FooDataWriter_impl::write_cdr(data, handle);
}

::DDS::ReturnCode_t
OpenRTM::CORBACdrDataDataWriter_impl::write (
    const OpenRTM::CORBACdrData & instance_data,
    ::DDS::InstanceHandle_t handle) THROW_ORB_EXCEPTIONS
{
    return DDS::OpenSplice::FooDataWriter_impl::write(&instance_data, handle);
}

::DDS::ReturnCode_t
OpenRTM::CORBACdrDataDataWriter_impl::write_w_timestamp (
    const CORBACdrData & instance_data,
    ::DDS::InstanceHandle_t handle,
    const ::DDS::Time_t & source_timestamp) THROW_ORB_EXCEPTIONS
{
    return DDS::OpenSplice::FooDataWriter_impl::write_w_timestamp(&instance_data, handle, source_timestamp);
}

::DDS::ReturnCode_t
OpenRTM::CORBACdrDataDataWriter_impl::dispose (
    const OpenRTM::CORBACdrData & instance_data,
    ::DDS::InstanceHandle_t handle) THROW_ORB_EXCEPTIONS
{
    return DDS::OpenSplice::FooDataWriter_impl::dispose(&instance_data, handle);
}

::DDS::ReturnCode_t
OpenRTM::CORBACdrDataDataWriter_impl::dispose_w_timestamp (
    const CORBACdrData & instance_data,
    ::DDS::InstanceHandle_t handle,
    const ::DDS::Time_t & source_timestamp) THROW_ORB_EXCEPTIONS
{
    return DDS::OpenSplice::FooDataWriter_impl::dispose_w_timestamp(&instance_data, handle, source_timestamp);
}

::DDS::ReturnCode_t
OpenRTM::CORBACdrDataDataWriter_impl::writedispose (
    const OpenRTM::CORBACdrData & instance_data,
    ::DDS::InstanceHandle_t handle) THROW_ORB_EXCEPTIONS
{
    return DDS::OpenSplice::FooDataWriter_impl::writedispose(&instance_data, handle);
}

::DDS::ReturnCode_t
OpenRTM::CORBACdrDataDataWriter_impl::writedispose_w_timestamp (
    const CORBACdrData & instance_data,
    ::DDS::InstanceHandle_t handle,
    const ::DDS::Time_t & source_timestamp) THROW_ORB_EXCEPTIONS
{
    return DDS::OpenSplice::FooDataWriter_impl::writedispose_w_timestamp(&instance_data, handle, source_timestamp);
}

::DDS::ReturnCode_t
OpenRTM::CORBACdrDataDataWriter_impl::get_key_value (
    CORBACdrData & key_holder,
    ::DDS::InstanceHandle_t handle) THROW_ORB_EXCEPTIONS
{
    return DDS::OpenSplice::FooDataWriter_impl::get_key_value(&key_holder, handle);
}

::DDS::InstanceHandle_t
OpenRTM::CORBACdrDataDataWriter_impl::lookup_instance (
    const OpenRTM::CORBACdrData & instance_data) THROW_ORB_EXCEPTIONS
{
    return DDS::OpenSplice::FooDataWriter_impl::lookup_instance(&instance_data);
}

// DDS OpenRTM::CORBACdrData DataReader_impl Object Body
OpenRTM::CORBACdrDataDataReader_impl::CORBACdrDataDataReader_impl ()
{
    // Parent constructor takes care of everything.
}

OpenRTM::CORBACdrDataDataReader_impl::~CORBACdrDataDataReader_impl ()
{
    // Parent destructor takes care of everything.
}

DDS::ReturnCode_t
OpenRTM::CORBACdrDataDataReader_impl::init (
    DDS::OpenSplice::Subscriber *subscriber,
    const DDS::DataReaderQos &qos,
    DDS::OpenSplice::TopicDescription *a_topic,
    const char *name,
    DDS::OpenSplice::cxxCopyIn copyIn,
    DDS::OpenSplice::cxxCopyOut copyOut,
    DDS::OpenSplice::cxxReaderCopy readerCopy,
    void *cdrMarshaler)
{
    return DDS::OpenSplice::FooDataReader_impl::nlReq_init(
            subscriber, qos, a_topic, name, copyIn, copyOut, readerCopy, cdrMarshaler,
            this->dataSeqAlloc, this->dataSeqLength, this->dataSeqGetBuffer, this->dataSeqCopyOut);
}

::DDS::ReturnCode_t
OpenRTM::CORBACdrDataDataReader_impl::read (
    OpenRTM::CORBACdrDataSeq & received_data,
    ::DDS::SampleInfoSeq & info_seq,
    ::DDS::Long max_samples,
    ::DDS::SampleStateMask sample_states,
    ::DDS::ViewStateMask view_states,
    ::DDS::InstanceStateMask instance_states) THROW_ORB_EXCEPTIONS
{
    ::DDS::ReturnCode_t status = DDS::RETCODE_OK;

    status = check_preconditions(received_data, info_seq, max_samples);
    if ( status == ::DDS::RETCODE_OK ) {
        status = DDS::OpenSplice::FooDataReader_impl::read(&received_data, info_seq, max_samples, sample_states, view_states, instance_states);
    }
    return status;
}

::DDS::ReturnCode_t
OpenRTM::CORBACdrDataDataReader_impl::read_cdr(
    ::DDS::CDRSample & received_data,
    ::DDS::SampleInfo & info,
    ::DDS::SampleStateMask sample_states,
    ::DDS::ViewStateMask view_states,
    ::DDS::InstanceStateMask instance_states) THROW_ORB_EXCEPTIONS
{
    ::DDS::ReturnCode_t status = DDS::RETCODE_OK;
    status = DDS::OpenSplice::FooDataReader_impl::read_cdr(received_data, info, sample_states, view_states, instance_states);
    return status;
}


::DDS::ReturnCode_t
OpenRTM::CORBACdrDataDataReader_impl::take (
    OpenRTM::CORBACdrDataSeq & received_data,
    ::DDS::SampleInfoSeq & info_seq,
    ::DDS::Long max_samples,
    ::DDS::SampleStateMask sample_states,
    ::DDS::ViewStateMask view_states,
    ::DDS::InstanceStateMask instance_states) THROW_ORB_EXCEPTIONS
{
    ::DDS::ReturnCode_t status = DDS::RETCODE_OK;

    status = check_preconditions(received_data, info_seq, max_samples);
    if ( status == ::DDS::RETCODE_OK ) {
        status = DDS::OpenSplice::FooDataReader_impl::take(&received_data, info_seq, max_samples, sample_states, view_states, instance_states);
    }
    return status;
}

::DDS::ReturnCode_t
OpenRTM::CORBACdrDataDataReader_impl::read_w_condition (
    OpenRTM::CORBACdrDataSeq & received_data,
    ::DDS::SampleInfoSeq & info_seq,
    ::DDS::Long max_samples,
    ::DDS::ReadCondition_ptr a_condition) THROW_ORB_EXCEPTIONS
{
    ::DDS::ReturnCode_t status = DDS::RETCODE_OK;

    status = check_preconditions(received_data, info_seq, max_samples);
    if ( status == ::DDS::RETCODE_OK ) {
        status = DDS::OpenSplice::FooDataReader_impl::read_w_condition(&received_data, info_seq, max_samples, a_condition);
    }
    return status;
}

::DDS::ReturnCode_t
OpenRTM::CORBACdrDataDataReader_impl::take_w_condition (
    OpenRTM::CORBACdrDataSeq & received_data,
    ::DDS::SampleInfoSeq & info_seq,
    ::DDS::Long max_samples,
    ::DDS::ReadCondition_ptr a_condition) THROW_ORB_EXCEPTIONS
{
    ::DDS::ReturnCode_t status = DDS::RETCODE_OK;

    status = check_preconditions(received_data, info_seq, max_samples);
    if ( status == ::DDS::RETCODE_OK ) {
        status = DDS::OpenSplice::FooDataReader_impl::take_w_condition(&received_data, info_seq, max_samples, a_condition);
    }
    return status;
}

::DDS::ReturnCode_t
OpenRTM::CORBACdrDataDataReader_impl::read_next_sample (
    OpenRTM::CORBACdrData & received_data,
    ::DDS::SampleInfo & sample_info) THROW_ORB_EXCEPTIONS
{
    return DDS::OpenSplice::FooDataReader_impl::read_next_sample(&received_data, sample_info);
}

::DDS::ReturnCode_t
OpenRTM::CORBACdrDataDataReader_impl::take_next_sample (
    OpenRTM::CORBACdrData & received_data,
    ::DDS::SampleInfo & sample_info) THROW_ORB_EXCEPTIONS
{
    return DDS::OpenSplice::FooDataReader_impl::take_next_sample(&received_data, sample_info);
}

::DDS::ReturnCode_t
OpenRTM::CORBACdrDataDataReader_impl::read_instance (
    OpenRTM::CORBACdrDataSeq & received_data,
    ::DDS::SampleInfoSeq & info_seq,
    ::DDS::Long max_samples,
    ::DDS::InstanceHandle_t a_handle,
    ::DDS::SampleStateMask sample_states,
    ::DDS::ViewStateMask view_states,
    ::DDS::InstanceStateMask instance_states) THROW_ORB_EXCEPTIONS
{
    ::DDS::ReturnCode_t status;

    status = check_preconditions(received_data, info_seq, max_samples);
    if ( status == ::DDS::RETCODE_OK ) {
        status = DDS::OpenSplice::FooDataReader_impl::read_instance(&received_data, info_seq, max_samples, a_handle, sample_states, view_states, instance_states);
    }
    return status;
}

::DDS::ReturnCode_t
OpenRTM::CORBACdrDataDataReader_impl::take_instance (
    OpenRTM::CORBACdrDataSeq & received_data,
    ::DDS::SampleInfoSeq & info_seq,
    ::DDS::Long max_samples,
    ::DDS::InstanceHandle_t a_handle,
    ::DDS::SampleStateMask sample_states,
    ::DDS::ViewStateMask view_states,
    ::DDS::InstanceStateMask instance_states) THROW_ORB_EXCEPTIONS
{
    ::DDS::ReturnCode_t status;

    status = check_preconditions(received_data, info_seq, max_samples);
    if ( status == ::DDS::RETCODE_OK ) {
        status = DDS::OpenSplice::FooDataReader_impl::take_instance(&received_data, info_seq, max_samples, a_handle, sample_states, view_states, instance_states);
    }
    return status;
}

::DDS::ReturnCode_t
OpenRTM::CORBACdrDataDataReader_impl::read_next_instance (
    OpenRTM::CORBACdrDataSeq & received_data,
    ::DDS::SampleInfoSeq & info_seq,
    ::DDS::Long max_samples,
    ::DDS::InstanceHandle_t a_handle,
    ::DDS::SampleStateMask sample_states,
    ::DDS::ViewStateMask view_states,
    ::DDS::InstanceStateMask instance_states) THROW_ORB_EXCEPTIONS
{
    ::DDS::ReturnCode_t status;

    status = check_preconditions(received_data, info_seq, max_samples);
    if ( status == ::DDS::RETCODE_OK ) {
        status = DDS::OpenSplice::FooDataReader_impl::read_next_instance(&received_data, info_seq, max_samples, a_handle, sample_states, view_states, instance_states);
    }
    return status;
}

::DDS::ReturnCode_t
OpenRTM::CORBACdrDataDataReader_impl::take_next_instance (
    OpenRTM::CORBACdrDataSeq & received_data,
    ::DDS::SampleInfoSeq & info_seq,
    ::DDS::Long max_samples,
    ::DDS::InstanceHandle_t a_handle,
    ::DDS::SampleStateMask sample_states,
    ::DDS::ViewStateMask view_states,
    ::DDS::InstanceStateMask instance_states) THROW_ORB_EXCEPTIONS
{
    ::DDS::ReturnCode_t status;

    status = check_preconditions(received_data, info_seq, max_samples);
    if ( status == ::DDS::RETCODE_OK ) {
        status = DDS::OpenSplice::FooDataReader_impl::take_next_instance(&received_data, info_seq, max_samples, a_handle, sample_states, view_states, instance_states);
    }
    return status;
}

::DDS::ReturnCode_t
OpenRTM::CORBACdrDataDataReader_impl::read_next_instance_w_condition (
    OpenRTM::CORBACdrDataSeq & received_data,
    ::DDS::SampleInfoSeq & info_seq,
    ::DDS::Long max_samples,
    ::DDS::InstanceHandle_t a_handle,
    ::DDS::ReadCondition_ptr a_condition) THROW_ORB_EXCEPTIONS
{
    ::DDS::ReturnCode_t status;

    status = check_preconditions(received_data, info_seq, max_samples);
    if ( status == ::DDS::RETCODE_OK ) {
        status = DDS::OpenSplice::FooDataReader_impl::read_next_instance_w_condition(&received_data, info_seq, max_samples, a_handle, a_condition);
    }
    return status;
}

::DDS::ReturnCode_t
OpenRTM::CORBACdrDataDataReader_impl::take_next_instance_w_condition (
    OpenRTM::CORBACdrDataSeq & received_data,
    ::DDS::SampleInfoSeq & info_seq,
    ::DDS::Long max_samples,
    ::DDS::InstanceHandle_t a_handle,
    ::DDS::ReadCondition_ptr a_condition) THROW_ORB_EXCEPTIONS
{
    ::DDS::ReturnCode_t status;

    status = check_preconditions(received_data, info_seq, max_samples);
    if ( status == ::DDS::RETCODE_OK ) {
        status = DDS::OpenSplice::FooDataReader_impl::take_next_instance_w_condition(&received_data, info_seq, max_samples, a_handle, a_condition);
    }
    return status;
}

::DDS::ReturnCode_t
OpenRTM::CORBACdrDataDataReader_impl::return_loan (
    OpenRTM::CORBACdrDataSeq & received_data,
    ::DDS::SampleInfoSeq & info_seq) THROW_ORB_EXCEPTIONS
{
    ::DDS::ReturnCode_t result = ::DDS::RETCODE_OK;

    result = this->write_lock ();
    if (result == DDS::RETCODE_OK) {
        if ( received_data.length() > 0 ) {
            if (received_data.length() == info_seq.length() &&
                received_data.release() == info_seq.release() ) {
                if (!received_data.release()) {
                    result = DDS::OpenSplice::FooDataReader_impl::wlReq_return_loan( received_data.get_buffer(),
                                                                                     info_seq.get_buffer() );
                    if ( result == ::DDS::RETCODE_OK ) {
                        if ( !received_data.release() ) {
                            OpenRTM::CORBACdrDataSeq::freebuf( received_data.get_buffer(false) );
                            received_data.replace(0, 0, nullptr, false);
                            ::DDS::SampleInfoSeq::freebuf( info_seq.get_buffer(false) );
                            info_seq.replace(0, 0, nullptr, false);
                        }
                    }
                }
            } else {
                result = ::DDS::RETCODE_PRECONDITION_NOT_MET;
            }
        }
        this->unlock();
    }
    return result;
}

::DDS::ReturnCode_t
OpenRTM::CORBACdrDataDataReader_impl::get_key_value (
    OpenRTM::CORBACdrData & key_holder,
    ::DDS::InstanceHandle_t handle) THROW_ORB_EXCEPTIONS
{
    return DDS::OpenSplice::FooDataReader_impl::get_key_value(&key_holder, handle);
}

::DDS::InstanceHandle_t
OpenRTM::CORBACdrDataDataReader_impl::lookup_instance (
    const OpenRTM::CORBACdrData & instance) THROW_ORB_EXCEPTIONS
{
    return DDS::OpenSplice::FooDataReader_impl::lookup_instance(&instance);
}

::DDS::ReturnCode_t
OpenRTM::CORBACdrDataDataReader_impl::check_preconditions (
    OpenRTM::CORBACdrDataSeq & received_data,
    ::DDS::SampleInfoSeq & info_seq,
    ::DDS::Long max_samples)
{
    if ((max_samples < 0) && (max_samples != DDS::LENGTH_UNLIMITED)) {
        return DDS::RETCODE_BAD_PARAMETER;
    }

    /* Rule 1 : The values of len, max_len, and owns
     * for the two collections must be identical.
     */
    if ((received_data.length()  != info_seq.length())  ||
        (received_data.maximum() != info_seq.maximum()) ||
        (received_data.release() != info_seq.release()))
    {
        return DDS::RETCODE_PRECONDITION_NOT_MET;
    }

    /* Rule 4: If the input max_len>0 and the input owns==FALSE,
     * then the read operation will fail.
     */
    if ((info_seq.maximum() > 0) &&
        (info_seq.release() == false))
    {
        return DDS::RETCODE_PRECONDITION_NOT_MET;
    }

    /* Rule 5: If input max_len>0 and the input owns==TRUE,
     * then the read operation will...
     */
    if (info_seq.maximum() > 0) { /* owns is true, because of rule 4. */
        /* Rule 5a: If max_samples = LENGTH_UNLIMITED,
         * then at most max_len values will be copied.
         * Rule 5b: If max_samples <= max_len,
         * then at most max_samples values will be copied.
         */
        /* Rule 5c: If max_samples > max_len,
         * then the read operation will fail.
         */
        if ((max_samples != DDS::LENGTH_UNLIMITED) &&
            ((DDS::ULong)max_samples > info_seq.maximum())) {
            return DDS::RETCODE_PRECONDITION_NOT_MET;
        }
    }

    if ((max_samples == 0) ||
        ((info_seq.maximum() == 0) && (info_seq.release()))) {
        return DDS::RETCODE_NO_DATA;
    }

    return DDS::RETCODE_OK;
}

void *
OpenRTM::CORBACdrDataDataReader_impl::dataSeqAlloc (
    void * received_data,
    DDS::ULong len)
{
    OpenRTM::CORBACdrDataSeq *data_seq = reinterpret_cast<OpenRTM::CORBACdrDataSeq *>(received_data);
    data_seq->replace(len, len, data_seq->allocbuf(len), false);
    return data_seq->get_buffer();
}

void *
OpenRTM::CORBACdrDataDataReader_impl::dataSeqGetBuffer (
    void * received_data,
    DDS::ULong index)
{
	OpenRTM::CORBACdrDataSeq *data_seq = reinterpret_cast<OpenRTM::CORBACdrDataSeq *>(received_data);
	return &((*data_seq)[index]);
}

void
OpenRTM::CORBACdrDataDataReader_impl::dataSeqLength (
    void * received_data,
    DDS::ULong len)
{
    OpenRTM::CORBACdrDataSeq *data_seq = reinterpret_cast<OpenRTM::CORBACdrDataSeq *>(received_data);
    data_seq->length(len);
}

void
OpenRTM::CORBACdrDataDataReader_impl::dataSeqCopyOut (
    const void * from,
    void * to)
{
    OpenRTM::CORBACdrData *data = reinterpret_cast<OpenRTM::CORBACdrData *>(to);
    OpenSplice_OpenRTM_CORBACdrData_copyOut(from, data);
}

void
OpenRTM::CORBACdrDataDataReader_impl::copyDataOut (
    const void * from,
    void * to)
{
    OpenRTM::CORBACdrData *data = reinterpret_cast<OpenRTM::CORBACdrData *>(to);
    OpenSplice_OpenRTM_CORBACdrData_copyOut(from, data);
}


// DDS OpenRTM::CORBACdrData DataReaderView_impl Object Body
OpenRTM::CORBACdrDataDataReaderView_impl::CORBACdrDataDataReaderView_impl ()
{
    // Parent constructor takes care of everything.
}

OpenRTM::CORBACdrDataDataReaderView_impl::~CORBACdrDataDataReaderView_impl ()
{
    // Parent destructor takes care of everything.
}

DDS::ReturnCode_t
OpenRTM::CORBACdrDataDataReaderView_impl::init (
    DDS::OpenSplice::DataReader *reader,
    const char *name,
    const DDS::DataReaderViewQos &qos,
    DDS::OpenSplice::cxxCopyIn copyIn,
    DDS::OpenSplice::cxxCopyOut copyOut)
{
    return DDS::OpenSplice::FooDataReaderView_impl::nlReq_init(
            reader, name, qos, copyIn, copyOut, OpenRTM::CORBACdrDataDataReader_impl::dataSeqAlloc,
            OpenRTM::CORBACdrDataDataReader_impl::dataSeqLength);
}

::DDS::ReturnCode_t
OpenRTM::CORBACdrDataDataReaderView_impl::read (
    OpenRTM::CORBACdrDataSeq & received_data,
    ::DDS::SampleInfoSeq & info_seq,
    ::DDS::Long max_samples,
    ::DDS::SampleStateMask sample_states,
    ::DDS::ViewStateMask view_states,
    ::DDS::InstanceStateMask instance_states) THROW_ORB_EXCEPTIONS
{
    ::DDS::ReturnCode_t status;

    status = OpenRTM::CORBACdrDataDataReader_impl::check_preconditions(received_data, info_seq, max_samples);
    if ( status == ::DDS::RETCODE_OK ) {
        status = DDS::OpenSplice::FooDataReaderView_impl::read(&received_data, info_seq, max_samples, sample_states, view_states, instance_states);
    }
    return status;
}

::DDS::ReturnCode_t
OpenRTM::CORBACdrDataDataReaderView_impl::take (
    OpenRTM::CORBACdrDataSeq & received_data,
    ::DDS::SampleInfoSeq & info_seq,
    ::DDS::Long max_samples,
    ::DDS::SampleStateMask sample_states,
    ::DDS::ViewStateMask view_states,
    ::DDS::InstanceStateMask instance_states) THROW_ORB_EXCEPTIONS
{
    ::DDS::ReturnCode_t status;

    status = OpenRTM::CORBACdrDataDataReader_impl::check_preconditions(received_data, info_seq, max_samples);
    if ( status == ::DDS::RETCODE_OK ) {
        status = DDS::OpenSplice::FooDataReaderView_impl::take(&received_data, info_seq, max_samples, sample_states, view_states, instance_states);
    }
    return status;
}

::DDS::ReturnCode_t
OpenRTM::CORBACdrDataDataReaderView_impl::read_w_condition (
    OpenRTM::CORBACdrDataSeq & received_data,
    ::DDS::SampleInfoSeq & info_seq,
    ::DDS::Long max_samples,
    ::DDS::ReadCondition_ptr a_condition) THROW_ORB_EXCEPTIONS
{
    ::DDS::ReturnCode_t status;

    status = OpenRTM::CORBACdrDataDataReader_impl::check_preconditions(received_data, info_seq, max_samples);
    if ( status == ::DDS::RETCODE_OK ) {
        status = DDS::OpenSplice::FooDataReaderView_impl::read_w_condition(&received_data, info_seq, max_samples, a_condition);
    }
    return status;
}

::DDS::ReturnCode_t
OpenRTM::CORBACdrDataDataReaderView_impl::take_w_condition (
    OpenRTM::CORBACdrDataSeq & received_data,
    ::DDS::SampleInfoSeq & info_seq,
    ::DDS::Long max_samples,
    ::DDS::ReadCondition_ptr a_condition) THROW_ORB_EXCEPTIONS
{
    ::DDS::ReturnCode_t status;

    status = OpenRTM::CORBACdrDataDataReader_impl::check_preconditions(received_data, info_seq, max_samples);
    if ( status == ::DDS::RETCODE_OK ) {
        status = DDS::OpenSplice::FooDataReaderView_impl::take_w_condition(&received_data, info_seq, max_samples, a_condition);
    }
    return status;
}

::DDS::ReturnCode_t
OpenRTM::CORBACdrDataDataReaderView_impl::read_next_sample (
    OpenRTM::CORBACdrData & received_data,
    ::DDS::SampleInfo & sample_info) THROW_ORB_EXCEPTIONS
{
    return DDS::OpenSplice::FooDataReaderView_impl::read_next_sample(&received_data, sample_info);
}

::DDS::ReturnCode_t
OpenRTM::CORBACdrDataDataReaderView_impl::take_next_sample (
    OpenRTM::CORBACdrData & received_data,
    ::DDS::SampleInfo & sample_info) THROW_ORB_EXCEPTIONS
{
    return DDS::OpenSplice::FooDataReaderView_impl::take_next_sample(&received_data, sample_info);
}

::DDS::ReturnCode_t
OpenRTM::CORBACdrDataDataReaderView_impl::read_instance (
    OpenRTM::CORBACdrDataSeq & received_data,
    ::DDS::SampleInfoSeq & info_seq,
    ::DDS::Long max_samples,
    ::DDS::InstanceHandle_t a_handle,
    ::DDS::SampleStateMask sample_states,
    ::DDS::ViewStateMask view_states,
    ::DDS::InstanceStateMask instance_states) THROW_ORB_EXCEPTIONS
{
    ::DDS::ReturnCode_t status;

    status = OpenRTM::CORBACdrDataDataReader_impl::check_preconditions(received_data, info_seq, max_samples);
    if ( status == ::DDS::RETCODE_OK ) {
        status = DDS::OpenSplice::FooDataReaderView_impl::read_instance(&received_data, info_seq, max_samples, a_handle, sample_states, view_states, instance_states);
    }
    return status;
}

::DDS::ReturnCode_t
OpenRTM::CORBACdrDataDataReaderView_impl::take_instance (
    OpenRTM::CORBACdrDataSeq & received_data,
    ::DDS::SampleInfoSeq & info_seq,
    ::DDS::Long max_samples,
    ::DDS::InstanceHandle_t a_handle,
    ::DDS::SampleStateMask sample_states,
    ::DDS::ViewStateMask view_states,
    ::DDS::InstanceStateMask instance_states) THROW_ORB_EXCEPTIONS
{
    ::DDS::ReturnCode_t status;

    status = OpenRTM::CORBACdrDataDataReader_impl::check_preconditions(received_data, info_seq, max_samples);
    if ( status == ::DDS::RETCODE_OK ) {
        status = DDS::OpenSplice::FooDataReaderView_impl::take_instance(&received_data, info_seq, max_samples, a_handle, sample_states, view_states, instance_states);
    }
    return status;
}

::DDS::ReturnCode_t
OpenRTM::CORBACdrDataDataReaderView_impl::read_next_instance (
    OpenRTM::CORBACdrDataSeq & received_data,
    ::DDS::SampleInfoSeq & info_seq,
    ::DDS::Long max_samples,
    ::DDS::InstanceHandle_t a_handle,
    ::DDS::SampleStateMask sample_states,
    ::DDS::ViewStateMask view_states,
    ::DDS::InstanceStateMask instance_states) THROW_ORB_EXCEPTIONS
{
    ::DDS::ReturnCode_t status;

    status = OpenRTM::CORBACdrDataDataReader_impl::check_preconditions(received_data, info_seq, max_samples);
    if ( status == ::DDS::RETCODE_OK ) {
        status = DDS::OpenSplice::FooDataReaderView_impl::read_next_instance(&received_data, info_seq, max_samples, a_handle, sample_states, view_states, instance_states);
    }
    return status;
}

::DDS::ReturnCode_t
OpenRTM::CORBACdrDataDataReaderView_impl::take_next_instance (
    OpenRTM::CORBACdrDataSeq & received_data,
    ::DDS::SampleInfoSeq & info_seq,
    ::DDS::Long max_samples,
    ::DDS::InstanceHandle_t a_handle,
    ::DDS::SampleStateMask sample_states,
    ::DDS::ViewStateMask view_states,
    ::DDS::InstanceStateMask instance_states) THROW_ORB_EXCEPTIONS
{
    ::DDS::ReturnCode_t status;

    status = OpenRTM::CORBACdrDataDataReader_impl::check_preconditions(received_data, info_seq, max_samples);
    if ( status == ::DDS::RETCODE_OK ) {
        status = DDS::OpenSplice::FooDataReaderView_impl::take_next_instance(&received_data, info_seq, max_samples, a_handle, sample_states, view_states, instance_states);
    }
    return status;
}

::DDS::ReturnCode_t
OpenRTM::CORBACdrDataDataReaderView_impl::read_next_instance_w_condition (
    OpenRTM::CORBACdrDataSeq & received_data,
    ::DDS::SampleInfoSeq & info_seq,
    ::DDS::Long max_samples,
    ::DDS::InstanceHandle_t a_handle,
    ::DDS::ReadCondition_ptr a_condition) THROW_ORB_EXCEPTIONS
{
    ::DDS::ReturnCode_t status;

    status = OpenRTM::CORBACdrDataDataReader_impl::check_preconditions(received_data, info_seq, max_samples);
    if ( status == ::DDS::RETCODE_OK ) {
        status = DDS::OpenSplice::FooDataReaderView_impl::read_next_instance_w_condition(&received_data, info_seq, max_samples, a_handle, a_condition);
    }
    return status;
}

::DDS::ReturnCode_t
OpenRTM::CORBACdrDataDataReaderView_impl::take_next_instance_w_condition (
    OpenRTM::CORBACdrDataSeq & received_data,
    ::DDS::SampleInfoSeq & info_seq,
    ::DDS::Long max_samples,
    ::DDS::InstanceHandle_t a_handle,
    ::DDS::ReadCondition_ptr a_condition) THROW_ORB_EXCEPTIONS
{
    ::DDS::ReturnCode_t status;

    status = OpenRTM::CORBACdrDataDataReader_impl::check_preconditions(received_data, info_seq, max_samples);
    if ( status == ::DDS::RETCODE_OK ) {
        status = DDS::OpenSplice::FooDataReaderView_impl::take_next_instance_w_condition(&received_data, info_seq, max_samples, a_handle, a_condition);
    }
    return status;
}

::DDS::ReturnCode_t
OpenRTM::CORBACdrDataDataReaderView_impl::return_loan (
    OpenRTM::CORBACdrDataSeq & received_data,
    ::DDS::SampleInfoSeq & info_seq) THROW_ORB_EXCEPTIONS
{
    ::DDS::ReturnCode_t result = ::DDS::RETCODE_OK;

    result = this->write_lock ();
    if (result == DDS::RETCODE_OK) {
        if ( received_data.length() > 0 ) {
            if (received_data.length() == info_seq.length() &&
                received_data.release() == info_seq.release() ) {
                if (!received_data.release()) {
                    result = DDS::OpenSplice::FooDataReaderView_impl::wlReq_return_loan( received_data.get_buffer(),
                                                           info_seq.get_buffer() );

                    if ( result == ::DDS::RETCODE_OK ) {
                        if ( !received_data.release() ) {
                            OpenRTM::CORBACdrDataSeq::freebuf( received_data.get_buffer(false) );
                            received_data.replace(0, 0, nullptr, false);
                            ::DDS::SampleInfoSeq::freebuf( info_seq.get_buffer(false) );
                            info_seq.replace(0, 0, nullptr, false);
                        }
                    } else if ( result == ::DDS::RETCODE_NO_DATA ) {
                        if ( received_data.release() ) {
                            result = ::DDS::RETCODE_OK;
                        } else {
                            result = ::DDS::RETCODE_PRECONDITION_NOT_MET;
                        }
                    }
                }
            } else {
                result = ::DDS::RETCODE_PRECONDITION_NOT_MET;
            }
        }
        this->unlock();
    }
    return result;
}

::DDS::ReturnCode_t
OpenRTM::CORBACdrDataDataReaderView_impl::get_key_value (
    OpenRTM::CORBACdrData & key_holder,
    ::DDS::InstanceHandle_t handle) THROW_ORB_EXCEPTIONS
{
    return DDS::OpenSplice::FooDataReaderView_impl::get_key_value(&key_holder, handle);
}

::DDS::InstanceHandle_t
OpenRTM::CORBACdrDataDataReaderView_impl::lookup_instance (
    const OpenRTM::CORBACdrData & instance) THROW_ORB_EXCEPTIONS
{
    return DDS::OpenSplice::FooDataReaderView_impl::lookup_instance(&instance);
}
