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
#include "ctkDictionary.h"
#include <QDebug>

ctkVariant::ctkVariant():data(NULL),sz(0) {
    //qDebug() << "ctkVariant Default constructor";
}

ctkVariant::ctkVariant(const ctkVariant &other): data(other.data), sz(other.sz) {
    //qDebug() << "ctkVariant Copy constructor";
}

#ifdef Q_COMPILER_RVALUE_REFS
ctkVariant::ctkVariant(ctkVariant &&other)
    : data(other.data), sz(other.sz)
{
}
#endif

ctkVariant::~ctkVariant() {
    if (data != NULL) {
    }
    sz = 0;
    //qDebug() << "ctkVariant Destructor";
}

#ifdef ctkVariant_TEST_DELETER
static void ctkVariantDataDeleter(char *obj)
{
    delete obj;
    qDebug() << "delete the ctkVariant data";
}
#endif

void ctkVariant::createFromDataAndSize(const void *in_data, size_t in_sz) {
    sz = 0;
    if (in_data == NULL || in_sz == 0) {
        return;
    }
#ifdef ctkVariant_TEST_DELETER
    data = QSharedPointer<char>(new char[in_sz], ctkVariantDataDeleter);
#else
    data = QSharedPointer<char>(new char[in_sz]);
#endif
    if (!data.isNull()) {
        memcpy(data.data(), in_data, in_sz);
        sz = in_sz;
    }
}
