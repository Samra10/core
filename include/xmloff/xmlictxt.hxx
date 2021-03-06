/* -*- Mode: C++; tab-width: 4; indent-tabs-mode: nil; c-basic-offset: 4 -*- */
/*
 * This file is part of the LibreOffice project.
 *
 * This Source Code Form is subject to the terms of the Mozilla Public
 * License, v. 2.0. If a copy of the MPL was not distributed with this
 * file, You can obtain one at http://mozilla.org/MPL/2.0/.
 *
 * This file incorporates work covered by the following license notice:
 *
 *   Licensed to the Apache Software Foundation (ASF) under one or more
 *   contributor license agreements. See the NOTICE file distributed
 *   with this work for additional information regarding copyright
 *   ownership. The ASF licenses this file to you under the Apache
 *   License, Version 2.0 (the "License"); you may not use this file
 *   except in compliance with the License. You may obtain a copy of
 *   the License at http://www.apache.org/licenses/LICENSE-2.0 .
 */

#ifndef INCLUDED_XMLOFF_XMLICTXT_HXX
#define INCLUDED_XMLOFF_XMLICTXT_HXX

#include <sal/config.h>
#include <xmloff/dllapi.h>
#include <sal/types.h>
#include <com/sun/star/xml/sax/XAttributeList.hpp>
#include <com/sun/star/xml/sax/XFastContextHandler.hpp>
#include <tools/ref.hxx>
#include <rtl/ustring.hxx>
#include <tools/rtti.hxx>
#include <cppuhelper/implbase1.hxx>

class SvXMLNamespaceMap;
class SvXMLImport;

class XMLOFF_DLLPUBLIC SvXMLImportContext : public SvRefBase,
        public ::cppu::WeakImplHelper1< ::css::xml::sax::XFastContextHandler >
{
    friend class SvXMLImport;

    SvXMLImport& mrImport;

    sal_uInt16       mnPrefix;
    OUString maLocalName;

    SvXMLNamespaceMap   *mpRewindMap;

    SAL_DLLPRIVATE SvXMLNamespaceMap *GetRewindMap() const
    { return mpRewindMap; }
    SAL_DLLPRIVATE void SetRewindMap( SvXMLNamespaceMap *p ) { mpRewindMap = p; }

protected:

    SvXMLImport& GetImport() { return mrImport; }
    const SvXMLImport& GetImport() const { return mrImport; }

public:
    TYPEINFO();

    sal_uInt16 GetPrefix() const { return mnPrefix; }
    const OUString& GetLocalName() const { return maLocalName; }

    /** A contexts constructor does anything that is required if an element
     * starts. Namespace processing has been done already.
     * Note that virtual methods cannot be used inside constructors. Use
     * StartElement instead if this is required. */
    SvXMLImportContext( SvXMLImport& rImport, sal_uInt16 nPrfx,
                        const OUString& rLName );

    SvXMLImportContext( SvXMLImport& rImport );

    /** A contexts destructor does anything that is required if an element
     * ends. By default, nothing is done.
     * Note that virtual methods cannot be used inside destructors. Use
     * EndElement instead if this is required. */
    virtual ~SvXMLImportContext();

    /** Create a children element context. By default, the import's
     * CreateContext method is called to create a new default context. */
    virtual SvXMLImportContext *CreateChildContext( sal_uInt16 nPrefix,
                                   const OUString& rLocalName,
                                   const ::com::sun::star::uno::Reference< ::com::sun::star::xml::sax::XAttributeList >& xAttrList );

    /** StartElement is called after a context has been constructed and
     * before a elements context is parsed. It may be used for actions that
     * require virtual methods. The default is to do nothing. */
    virtual void StartElement( const ::com::sun::star::uno::Reference< ::com::sun::star::xml::sax::XAttributeList >& xAttrList );

    /** EndElement is called before a context will be destructed, but
     * after a elements context has been parsed. It may be used for actions
     * that require virtual methods. The default is to do nothing. */
    virtual void EndElement();

    /** This method is called for all characters that are contained in the
     * current element. The default is to ignore them. */
    virtual void Characters( const OUString& rChars );

    // ::com::sun::star::xml::sax::XFastContextHandler:
    virtual void SAL_CALL startFastElement (sal_Int32 Element,
        const css::uno::Reference< css::xml::sax::XFastAttributeList >& Attribs)
        throw (css::uno::RuntimeException, css::xml::sax::SAXException, std::exception) SAL_OVERRIDE;

    virtual void SAL_CALL startUnknownElement(const OUString & Namespace, const OUString & Name,
        const css::uno::Reference< css::xml::sax::XFastAttributeList > & Attribs)
        throw (css::uno::RuntimeException, css::xml::sax::SAXException, std::exception) SAL_OVERRIDE;

    virtual void SAL_CALL endFastElement(sal_Int32 Element)
        throw (css::uno::RuntimeException, css::xml::sax::SAXException, std::exception) SAL_OVERRIDE;

    virtual void SAL_CALL endUnknownElement(const OUString & Namespace, const OUString & Name)
        throw (css::uno::RuntimeException, css::xml::sax::SAXException, std::exception) SAL_OVERRIDE;

    virtual css::uno::Reference< XFastContextHandler >  SAL_CALL createFastChildContext(sal_Int32 Element,
        const css::uno::Reference<css::xml::sax::XFastAttributeList>& Attribs)
        throw (css::uno::RuntimeException, css::xml::sax::SAXException, std::exception) SAL_OVERRIDE;

    virtual css::uno::Reference< css::xml::sax::XFastContextHandler > SAL_CALL createUnknownChildContext(
        const OUString & Namespace, const OUString & Name,
        const css::uno::Reference< css::xml::sax::XFastAttributeList > & Attribs)
        throw (css::uno::RuntimeException, css::xml::sax::SAXException, std::exception) SAL_OVERRIDE;

    virtual void SAL_CALL characters(const OUString & aChars)
        throw (css::uno::RuntimeException, css::xml::sax::SAXException, std::exception) SAL_OVERRIDE;

    // #i124143# allow to copy evtl. useful data from another temporary import context, e.g. used to
    // support multiple images and to rescue evtl. GluePoints imported with one of the
    // to be deprecated contents
    virtual void onDemandRescueUsefulDataFromTemporary( const SvXMLImportContext& rCandidate );
};

typedef tools::SvRef<SvXMLImportContext> SvXMLImportContextRef;

#endif // INCLUDED_XMLOFF_XMLICTXT_HXX

/* vim:set shiftwidth=4 softtabstop=4 expandtab: */
