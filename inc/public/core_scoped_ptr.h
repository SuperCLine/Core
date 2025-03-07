/*------------------------------------------------------------------------------
|
| COPYRIGHT (C) 2018 - 2026 All Right Reserved
|
| FILE NAME  : \core\inc\public\core_scoped_ptr.h
| AUTHOR     : https://supercline.com/
| PURPOSE    :
|
| SPEC       :
|
| MODIFICATION HISTORY
|
| Ver      Date            By              Details
| -----    -----------    -------------   ----------------------
| 1.0      2019-9-28      SuperCLine           Created
|
+-----------------------------------------------------------------------------*/


#ifndef _CORE_SCOPED_PTR_H_
#define _CORE_SCOPED_PTR_H_


__BEGIN_NAMESPACE


enum class EFreePolicy :uint8
{
	Delete = 1,
	Deletearray = 2,
	Release = 3,
};


template <typename T, typename free_policy_type = EFreePolicy>
class core_scoped_ptr : private nocopyable
{
public:
    explicit core_scoped_ptr(T* ptr, free_policy_type policy);
    ~core_scoped_ptr(void);

    T* detach(void);
	T* get(void);

private:
    T* m_ptr;
    free_policy_type m_policy;
};

template <typename T, typename free_policy_type /*= EFreePolicy*/>
core_scoped_ptr<T, free_policy_type>::core_scoped_ptr(T* ptr, free_policy_type policy)
    : m_ptr(ptr)
    , m_policy(policy)
{

}

template <typename T, typename free_policy_type /*= EFreePolicy*/>
core_scoped_ptr<T, free_policy_type>::~core_scoped_ptr(void)
{
    if (m_ptr)
    {
        switch (m_policy)
        {
        case EFP_DELETE:
            delete m_ptr;
            break;
        case EFP_DELETEARRAY:
            delete[] m_ptr;
            break;
        case EFP_RELEASE:
            m_ptr->release();
            break;
        }
        m_ptr = 0;
    }
}

template <typename T, typename free_policy_type /*= EFreePolicy*/>
T* core_scoped_ptr<T, free_policy_type>::detach(void)
{
    T* p = m_ptr;
    m_ptr = 0;

    return p;
}

template <typename T, typename free_policy_type /*= EFreePolicy*/>
T* core_scoped_ptr<T, free_policy_type>::get(void)
{
	return m_ptr;
}


__END_NAMESPACE


#endif //_CORE_SCOPED_PTR_H_