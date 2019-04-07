#ifndef CORBACDRDATADCPS_IMPL_H_
#define CORBACDRDATADCPS_IMPL_H_

#include "ccpp.h"
#include "ccpp_CORBACdrData.h"
#include "TypeSupportMetaHolder.h"
#include "TypeSupport.h"
#include "FooDataWriter_impl.h"
#include "FooDataReader_impl.h"
#include "FooDataReaderView_impl.h"
#include <string>


namespace OpenRTM {

    class  CORBACdrDataTypeSupportMetaHolder : public ::DDS::OpenSplice::TypeSupportMetaHolder
    {
    public:
        CORBACdrDataTypeSupportMetaHolder (const char *datatype, const char *keys, const char* descriptor);
        virtual ~CORBACdrDataTypeSupportMetaHolder ();
    
    private:
        ::DDS::OpenSplice::TypeSupportMetaHolder * clone();
    
        ::DDS::OpenSplice::DataWriter * create_datawriter ();
    
        ::DDS::OpenSplice::DataReader * create_datareader ();
    
        ::DDS::OpenSplice::DataReaderView * create_view ();

        std::string m_datatype;
        std::string m_descriptor;
        std::string m_keys;
    };
    
    class  CORBACdrDataTypeSupport : public virtual CORBACdrDataTypeSupportInterface,
                                                       public ::DDS::OpenSplice::TypeSupport
    {
    public:
        CORBACdrDataTypeSupport (const char* datatype, const char* keys, const char* descriptor);
    
        virtual ~CORBACdrDataTypeSupport ();
    
    private:
        CORBACdrDataTypeSupport (const CORBACdrDataTypeSupport &);
    
        CORBACdrDataTypeSupport & operator= (const CORBACdrDataTypeSupport &);
    };
    
    typedef CORBACdrDataTypeSupportInterface_var CORBACdrDataTypeSupport_var;
    typedef CORBACdrDataTypeSupportInterface_ptr CORBACdrDataTypeSupport_ptr;
    
    class  CORBACdrDataDataWriter_impl : public virtual CORBACdrDataDataWriter,
                                                           public ::DDS::OpenSplice::FooDataWriter_impl
    {
        friend class DDS::OpenSplice::Publisher;
        friend class CORBACdrDataTypeSupportMetaHolder;
    
    public:
        virtual ::DDS::InstanceHandle_t register_instance (
            const CORBACdrData & instance_data) THROW_ORB_EXCEPTIONS;
    
        virtual ::DDS::InstanceHandle_t register_instance_w_timestamp (
            const CORBACdrData & instance_data,
            const ::DDS::Time_t & source_timestamp) THROW_ORB_EXCEPTIONS;
    
        virtual ::DDS::ReturnCode_t unregister_instance (
            const CORBACdrData & instance_data,
            ::DDS::InstanceHandle_t handle) THROW_ORB_EXCEPTIONS;
    
        virtual ::DDS::ReturnCode_t unregister_instance_w_timestamp (
            const CORBACdrData & instance_data,
            ::DDS::InstanceHandle_t handle,
            const ::DDS::Time_t & source_timestamp) THROW_ORB_EXCEPTIONS;
    
        virtual ::DDS::ReturnCode_t write (
            const CORBACdrData & instance_data,
            ::DDS::InstanceHandle_t handle) THROW_ORB_EXCEPTIONS;

        virtual ::DDS::ReturnCode_t write_cdr(
            const ::DDS::CDRSample & data,
            ::DDS::InstanceHandle_t handle) THROW_ORB_EXCEPTIONS;
    
        virtual ::DDS::ReturnCode_t write_w_timestamp (
            const CORBACdrData & instance_data,
            ::DDS::InstanceHandle_t handle,
            const ::DDS::Time_t & source_timestamp) THROW_ORB_EXCEPTIONS;
    
        virtual ::DDS::ReturnCode_t dispose (
            const CORBACdrData & instance_data,
            ::DDS::InstanceHandle_t handle) THROW_ORB_EXCEPTIONS;
    
        virtual ::DDS::ReturnCode_t dispose_w_timestamp (
            const CORBACdrData & instance_data,
            ::DDS::InstanceHandle_t handle,
            const ::DDS::Time_t & source_timestamp) THROW_ORB_EXCEPTIONS;
    
        virtual ::DDS::ReturnCode_t writedispose (
            const CORBACdrData & instance_data,
            ::DDS::InstanceHandle_t handle) THROW_ORB_EXCEPTIONS;
    
        virtual ::DDS::ReturnCode_t writedispose_w_timestamp (
            const CORBACdrData & instance_data,
            ::DDS::InstanceHandle_t handle,
            const ::DDS::Time_t & source_timestamp) THROW_ORB_EXCEPTIONS;
    
        virtual ::DDS::ReturnCode_t get_key_value (
            CORBACdrData & key_holder,
            ::DDS::InstanceHandle_t handle) THROW_ORB_EXCEPTIONS;
    
        virtual ::DDS::InstanceHandle_t lookup_instance (
            const CORBACdrData & instance_data) THROW_ORB_EXCEPTIONS;
    
    protected:
        CORBACdrDataDataWriter_impl ();
    
        virtual ~CORBACdrDataDataWriter_impl ();
    
        virtual DDS::ReturnCode_t init (
                        DDS::OpenSplice::Publisher *publisher,
                        DDS::OpenSplice::DomainParticipant *participant,
                        const DDS::DataWriterQos &qos,
                        DDS::OpenSplice::Topic *a_topic,
                        const char *name,
                        DDS::OpenSplice::cxxCopyIn copyIn,
                        DDS::OpenSplice::cxxCopyOut copyOut,
                        u_writerCopy writerCopy,
                        void *cdrMarshaler);
    
    private:
        CORBACdrDataDataWriter_impl (const CORBACdrDataDataWriter_impl &);
    
        CORBACdrDataDataWriter_impl & operator= (const CORBACdrDataDataWriter_impl &);
    };
    
    class  CORBACdrDataDataReader_impl : public virtual CORBACdrDataDataReader,
                                                           public ::DDS::OpenSplice::FooDataReader_impl
    {
        friend class DDS::OpenSplice::Subscriber;
        friend class CORBACdrDataTypeSupportMetaHolder;
        friend class CORBACdrDataDataReaderView_impl;
    
    public:
        virtual ::DDS::ReturnCode_t read (
            CORBACdrDataSeq & received_data,
            ::DDS::SampleInfoSeq & info_seq,
            ::DDS::Long max_samples,
            ::DDS::SampleStateMask sample_states,
            ::DDS::ViewStateMask view_states,
            ::DDS::InstanceStateMask instance_states) THROW_ORB_EXCEPTIONS;

        virtual DDS::Long read_cdr(
            ::DDS::CDRSample& received_data, 
            ::DDS::SampleInfo& info,
            ::DDS::Long max_samples,
            ::DDS::ULong sample_states,
            ::DDS::ULong view_states) THROW_ORB_EXCEPTIONS;

    
        virtual ::DDS::ReturnCode_t take (
            CORBACdrDataSeq & received_data,
            ::DDS::SampleInfoSeq & info_seq,
            ::DDS::Long max_samples,
            ::DDS::SampleStateMask sample_states,
            ::DDS::ViewStateMask view_states,
            ::DDS::InstanceStateMask instance_states) THROW_ORB_EXCEPTIONS;
    
        virtual ::DDS::ReturnCode_t read_w_condition (
            CORBACdrDataSeq & received_data,
            ::DDS::SampleInfoSeq & info_seq,
            ::DDS::Long max_samples,
            ::DDS::ReadCondition_ptr a_condition) THROW_ORB_EXCEPTIONS;
    
        virtual ::DDS::ReturnCode_t take_w_condition (
            CORBACdrDataSeq & received_data,
            ::DDS::SampleInfoSeq & info_seq,
            ::DDS::Long max_samples,
            ::DDS::ReadCondition_ptr a_condition) THROW_ORB_EXCEPTIONS;
    
        virtual ::DDS::ReturnCode_t read_next_sample (
            CORBACdrData & received_data,
            ::DDS::SampleInfo & sample_info) THROW_ORB_EXCEPTIONS;
    
        virtual ::DDS::ReturnCode_t take_next_sample (
            CORBACdrData & received_data,
            ::DDS::SampleInfo & sample_info) THROW_ORB_EXCEPTIONS;
    
        virtual ::DDS::ReturnCode_t read_instance (
            CORBACdrDataSeq & received_data,
            ::DDS::SampleInfoSeq & info_seq,
            ::DDS::Long max_samples,
            ::DDS::InstanceHandle_t a_handle,
            ::DDS::SampleStateMask sample_states,
            ::DDS::ViewStateMask view_states,
            ::DDS::InstanceStateMask instance_states) THROW_ORB_EXCEPTIONS;
    
        virtual ::DDS::ReturnCode_t take_instance (
            CORBACdrDataSeq & received_data,
            ::DDS::SampleInfoSeq & info_seq,
            ::DDS::Long max_samples,
            ::DDS::InstanceHandle_t a_handle,
            ::DDS::SampleStateMask sample_states,
            ::DDS::ViewStateMask view_states,
            ::DDS::InstanceStateMask instance_states) THROW_ORB_EXCEPTIONS;
    
        virtual ::DDS::ReturnCode_t read_next_instance (
            CORBACdrDataSeq & received_data,
            ::DDS::SampleInfoSeq & info_seq,
            ::DDS::Long max_samples,
            ::DDS::InstanceHandle_t a_handle,
            ::DDS::SampleStateMask sample_states,
            ::DDS::ViewStateMask view_states,
            ::DDS::InstanceStateMask instance_states) THROW_ORB_EXCEPTIONS;
    
        virtual ::DDS::ReturnCode_t take_next_instance (
            CORBACdrDataSeq & received_data,
            ::DDS::SampleInfoSeq & info_seq,
            ::DDS::Long max_samples,
            ::DDS::InstanceHandle_t a_handle,
            ::DDS::SampleStateMask sample_states,
            ::DDS::ViewStateMask view_states,
            ::DDS::InstanceStateMask instance_states) THROW_ORB_EXCEPTIONS;
    
        virtual ::DDS::ReturnCode_t read_next_instance_w_condition (
            CORBACdrDataSeq & received_data,
            ::DDS::SampleInfoSeq & info_seq,
            ::DDS::Long max_samples,
            ::DDS::InstanceHandle_t a_handle,
            ::DDS::ReadCondition_ptr a_condition) THROW_ORB_EXCEPTIONS;
    
        virtual ::DDS::ReturnCode_t take_next_instance_w_condition (
            CORBACdrDataSeq & received_data,
            ::DDS::SampleInfoSeq & info_seq,
            ::DDS::Long max_samples,
            ::DDS::InstanceHandle_t a_handle,
            ::DDS::ReadCondition_ptr a_condition) THROW_ORB_EXCEPTIONS;
    
        virtual ::DDS::ReturnCode_t return_loan (
            CORBACdrDataSeq & received_data,
            ::DDS::SampleInfoSeq & info_seq) THROW_ORB_EXCEPTIONS;
    
        virtual ::DDS::ReturnCode_t get_key_value (
            CORBACdrData & key_holder,
            ::DDS::InstanceHandle_t handle) THROW_ORB_EXCEPTIONS;
    
        virtual ::DDS::InstanceHandle_t lookup_instance (
            const CORBACdrData & instance) THROW_ORB_EXCEPTIONS;
    
    protected:
        CORBACdrDataDataReader_impl ();
    
        virtual ~CORBACdrDataDataReader_impl ();
    
        DDS::ReturnCode_t init (
                DDS::OpenSplice::Subscriber *subscriber,
                const DDS::DataReaderQos &qos,
                DDS::OpenSplice::TopicDescription *a_topic,
                const char *name,
                DDS::OpenSplice::cxxCopyIn copyIn,
                DDS::OpenSplice::cxxCopyOut copyOut,
                DDS::OpenSplice::cxxReaderCopy readerCopy,
                void *cdrMarshaler);
    
        static void* dataSeqAlloc (
            void * data_values,
            DDS::ULong len);
    
        static void dataSeqLength (
            void * data_values,
            DDS::ULong len);
    
        static void * dataSeqGetBuffer (
            void * data_values,
            DDS::ULong index);
    
        static void dataSeqCopyOut (
            const void * from,
            void * received_data);
        static void copyDataOut(const void *from, void *to);
    
    private:
        CORBACdrDataDataReader_impl (const CORBACdrDataDataReader_impl &);
        CORBACdrDataDataReader_impl & operator= (const CORBACdrDataDataReader_impl &);
    
        static ::DDS::ReturnCode_t check_preconditions (
            CORBACdrDataSeq & received_data,
            ::DDS::SampleInfoSeq & info_seq,
            ::DDS::Long max_samples);
    };
    
    class  CORBACdrDataDataReaderView_impl : public virtual CORBACdrDataDataReaderView,
                                                               public ::DDS::OpenSplice::FooDataReaderView_impl
    {
        friend class DDS::OpenSplice::DataReader;
        friend class CORBACdrDataTypeSupportMetaHolder;
    
    public:
        virtual ::DDS::ReturnCode_t read (
            CORBACdrDataSeq & received_data,
            ::DDS::SampleInfoSeq & info_seq,
            ::DDS::Long max_samples,
            ::DDS::SampleStateMask sample_states,
            ::DDS::ViewStateMask view_states,
            ::DDS::InstanceStateMask instance_states) THROW_ORB_EXCEPTIONS;
    
        virtual ::DDS::ReturnCode_t take (
            CORBACdrDataSeq & received_data,
            ::DDS::SampleInfoSeq & info_seq,
            ::DDS::Long max_samples,
            ::DDS::SampleStateMask sample_states,
            ::DDS::ViewStateMask view_states,
            ::DDS::InstanceStateMask instance_states) THROW_ORB_EXCEPTIONS;
    
        virtual ::DDS::ReturnCode_t read_w_condition (
            CORBACdrDataSeq & received_data,
            ::DDS::SampleInfoSeq & info_seq,
            ::DDS::Long max_samples,
            ::DDS::ReadCondition_ptr a_condition) THROW_ORB_EXCEPTIONS;
    
        virtual ::DDS::ReturnCode_t take_w_condition (
            CORBACdrDataSeq & received_data,
            ::DDS::SampleInfoSeq & info_seq,
            ::DDS::Long max_samples,
            ::DDS::ReadCondition_ptr a_condition) THROW_ORB_EXCEPTIONS;
    
        virtual ::DDS::ReturnCode_t read_next_sample (
            CORBACdrData & received_data,
            ::DDS::SampleInfo & sample_info) THROW_ORB_EXCEPTIONS;
    
        virtual ::DDS::ReturnCode_t take_next_sample (
            CORBACdrData & received_data,
            ::DDS::SampleInfo & sample_info) THROW_ORB_EXCEPTIONS;
    
        virtual ::DDS::ReturnCode_t read_instance (
            CORBACdrDataSeq & received_data,
            ::DDS::SampleInfoSeq & info_seq,
            ::DDS::Long max_samples,
            ::DDS::InstanceHandle_t a_handle,
            ::DDS::SampleStateMask sample_states,
            ::DDS::ViewStateMask view_states,
            ::DDS::InstanceStateMask instance_states) THROW_ORB_EXCEPTIONS;
    
        virtual ::DDS::ReturnCode_t take_instance (
            CORBACdrDataSeq & received_data,
            ::DDS::SampleInfoSeq & info_seq,
            ::DDS::Long max_samples,
            ::DDS::InstanceHandle_t a_handle,
            ::DDS::SampleStateMask sample_states,
            ::DDS::ViewStateMask view_states,
            ::DDS::InstanceStateMask instance_states) THROW_ORB_EXCEPTIONS;
    
        virtual ::DDS::ReturnCode_t read_next_instance (
            CORBACdrDataSeq & received_data,
            ::DDS::SampleInfoSeq & info_seq,
            ::DDS::Long max_samples,
            ::DDS::InstanceHandle_t a_handle,
            ::DDS::SampleStateMask sample_states,
            ::DDS::ViewStateMask view_states,
            ::DDS::InstanceStateMask instance_states) THROW_ORB_EXCEPTIONS;
    
        virtual ::DDS::ReturnCode_t take_next_instance (
            CORBACdrDataSeq & received_data,
            ::DDS::SampleInfoSeq & info_seq,
            ::DDS::Long max_samples,
            ::DDS::InstanceHandle_t a_handle,
            ::DDS::SampleStateMask sample_states,
            ::DDS::ViewStateMask view_states,
            ::DDS::InstanceStateMask instance_states) THROW_ORB_EXCEPTIONS;
    
        virtual ::DDS::ReturnCode_t read_next_instance_w_condition (
            CORBACdrDataSeq & received_data,
            ::DDS::SampleInfoSeq & info_seq,
            ::DDS::Long max_samples,
            ::DDS::InstanceHandle_t a_handle,
            ::DDS::ReadCondition_ptr a_condition) THROW_ORB_EXCEPTIONS;
    
        virtual ::DDS::ReturnCode_t take_next_instance_w_condition (
            CORBACdrDataSeq & received_data,
            ::DDS::SampleInfoSeq & info_seq,
            ::DDS::Long max_samples,
            ::DDS::InstanceHandle_t a_handle,
            ::DDS::ReadCondition_ptr a_condition) THROW_ORB_EXCEPTIONS;
    
        virtual ::DDS::ReturnCode_t return_loan (
            CORBACdrDataSeq & received_data,
            ::DDS::SampleInfoSeq & info_seq) THROW_ORB_EXCEPTIONS;
    
        virtual ::DDS::ReturnCode_t get_key_value (
            CORBACdrData & key_holder,
            ::DDS::InstanceHandle_t handle) THROW_ORB_EXCEPTIONS;
    
        virtual ::DDS::InstanceHandle_t lookup_instance (
            const CORBACdrData & instance) THROW_ORB_EXCEPTIONS;
    
    protected:
        CORBACdrDataDataReaderView_impl ();
    
        virtual ~CORBACdrDataDataReaderView_impl ();
    
        virtual DDS::ReturnCode_t init (
            DDS::OpenSplice::DataReader *reader,
            const char *name,
            const DDS::DataReaderViewQos &qos,
            DDS::OpenSplice::cxxCopyIn copyIn,
            DDS::OpenSplice::cxxCopyOut copyOut);
    
    private:
        CORBACdrDataDataReaderView_impl (const CORBACdrDataDataReaderView_impl &);
    
        CORBACdrDataDataReaderView_impl & operator= (const CORBACdrDataDataReaderView_impl &);
    };
    
}

#undef OS_API
#endif
