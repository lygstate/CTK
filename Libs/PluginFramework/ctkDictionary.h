/*=============================================================================

  Library: CTK

  Copyright (c) German Cancer Research Center,
    Division of Medical and Biological Informatics

  Licensed under the Apache License, Version 2.0 (the "License");
  you may not use this file except in compliance with the License.
  You may obtain a copy of the License at

    http://www.apache.org/licenses/LICENSE-2.0

  Unless required by applicable law or agreed to in writing, software
  distributed under the License is distributed on an "AS IS" BASIS,
  WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
  See the License for the specific language governing permissions and
  limitations under the License.

=============================================================================*/


#ifndef CTKDICTIONARY_H
#define CTKDICTIONARY_H

#include <ctkPluginFrameworkExport.h>


#include <QSharedPointer>
#include <QVariant>
#include <QHash>
#include <QString>

/*
The ctkVariant is used to storage *plain old data*(POD), use to transfer data between
differnt plugins. such as tranfer protocol data, bus data that contains lots
of data entries.
Use QSharedPointer to storage the unique copy of the pod, so that avoid
unneeded copies of the POD. and it's freed when necessary.(Because QVariant will
copy data frequently and the POD data may be very large.
*/
class CTK_PLUGINFW_EXPORT ctkVariant{
public:
    ctkVariant();

    template<typename T>
    ctkVariant(const T &x):data(NULL) {
        createFromDataAndSize(static_cast<const void*>(&x), sizeof(x));
    }

    ctkVariant(const ctkVariant &);
#ifdef Q_COMPILER_RVALUE_REFS
    ctkVariant(ctkVariant &&other);
#endif

    ~ctkVariant();

private:
    // Q_DISABLE_COPY(ctkVariant)
    ctkVariant &operator=(const ctkVariant &) Q_DECL_EQ_DELETE;

public:
    template <typename T>
    inline static QVariant fromStruct(T &x);

    template <typename T>
    inline static T* toStruct(const QVariant &x);
private:
    template <typename T>
    inline T* toStruct() const {
        if (sizeof(T) == sz) {
            return reinterpret_cast<T*>(data.data());
        }
        return NULL;
    }

    void createFromDataAndSize(const void *data, size_t sz);
    QSharedPointer<char> data;
    size_t sz;
};

Q_DECLARE_METATYPE(ctkVariant)

template <typename T>
inline static QVariant ctkVariant::fromStruct(T &x) {
    return QVariant::fromValue(ctkVariant(x));
}

template <typename T>
inline static T *ctkVariant::toStruct(const QVariant &x) {
    if (x.canConvert<ctkVariant>()) {
        return static_cast<ctkVariant const *>(x.data())->toStruct<T>();
    }
    return NULL;
}

template<typename T> class TypeIdentifier
{
public:
	inline static const char *id()
	{
#if defined (_MSC_VER)
		return __FUNCTION__;
#elif defined(__GNUC__)
		return __PRETTY_FUNCTION__;
#else
		return typeid(T).name();
#endif
	}
private:
	TypeIdentifier();
};

/**
 * \ingroup PluginFramework
 *
 * A typedef for a QString to QVariant hash map. Typically used for service properties.
 *
 * \note This is equivalent to using ctkProperties.
 */
typedef QHash<QString,QVariant> ctkDictionary;

template <typename T>
void ctkDictionarySet(ctkDictionary &dict, T const &v)
{
	dict[TypeIdentifier<T>::id()] = ctkVariant::fromStruct(v);
}

template <typename T>
T *ctkDictionaryGet(ctkDictionary &dict)
{
	return ctkVariant::toStruct<T>(dict.value(TypeIdentifier<T>::id()));
}

#endif // CTKDICTIONARY_H
