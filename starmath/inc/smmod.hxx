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

#ifndef INCLUDED_STARMATH_INC_SMMOD_HXX
#define INCLUDED_STARMATH_INC_SMMOD_HXX

#include <tools/resary.hxx>
#include <svl/lstner.hxx>
#include <svtools/colorcfg.hxx>

#include <tools/shl.hxx>
#include "tools/rc.hxx"
#include <sfx2/module.hxx>

#include "starmath.hrc"

#include <unotools/options.hxx>

class SfxObjectFactory;
class SmConfig;
class SmModule;
class SmSymbolManager;

/*************************************************************************
|*
|* This subclass of <SfxModule> (which is a subclass of <SfxShell>) is
|* linked to the DLL. One instance of this class exists while the DLL is
|* loaded.
|*
|* SdModule is like to be compared with the <SfxApplication>-subclass.
|*
|* Remember: Don`t export this class! It uses DLL-internal symbols.
|*
\************************************************************************/

class SvtSysLocale;
class VirtualDevice;



class SmResId : public ResId
{
public:
    SmResId(sal_uInt16 nId);
};

#define SM_RESSTR(x) SmResId(x).toString()

class SmLocalizedSymbolData : public Resource
{
    ResStringArray      aUiSymbolNamesAry;
    ResStringArray      aExportSymbolNamesAry;
    ResStringArray      aUiSymbolSetNamesAry;
    ResStringArray      aExportSymbolSetNamesAry;

public:
    SmLocalizedSymbolData();
    ~SmLocalizedSymbolData();

    const ResStringArray& GetUiSymbolNamesArray() const     { return aUiSymbolNamesAry; }
    const ResStringArray& GetExportSymbolNamesArray() const { return aExportSymbolNamesAry; }
    const OUString        GetUiSymbolName( const OUString &rExportName ) const;
    const OUString        GetExportSymbolName( const OUString &rUiName ) const;

    const ResStringArray& GetUiSymbolSetNamesArray() const     { return aUiSymbolSetNamesAry; }
    const ResStringArray& GetExportSymbolSetNamesArray() const { return aExportSymbolSetNamesAry; }
    const OUString        GetUiSymbolSetName( const OUString &rExportName ) const;
    const OUString        GetExportSymbolSetName( const OUString &rUiName ) const;
};

class SmModule : public SfxModule, utl::ConfigurationListener
{
    svtools::ColorConfig        *pColorConfig;
    SmConfig                *pConfig;
    SmLocalizedSymbolData   *pLocSymbolData;
    SvtSysLocale            *pSysLocale;
    VirtualDevice           *pVirtualDev;

    void _CreateSysLocale() const;
    void _CreateVirtualDev() const;

    void ApplyColorConfigValues( const svtools::ColorConfig &rColorCfg );

public:
    TYPEINFO_OVERRIDE();
    SFX_DECL_INTERFACE(SFX_INTERFACE_SMA_START + 0)

private:
    /// SfxInterface initializer.
    static void InitInterface_Impl();

public:
    SmModule(SfxObjectFactory* pObjFact);
    virtual ~SmModule();

    virtual void ConfigurationChanged( utl::ConfigurationBroadcaster*, sal_uInt32 ) SAL_OVERRIDE;

    svtools::ColorConfig &  GetColorConfig();

    SmConfig *              GetConfig();
    SmSymbolManager &       GetSymbolManager();

    SmLocalizedSymbolData &   GetLocSymbolData() const;

    void GetState(SfxItemSet&);

    const SvtSysLocale& GetSysLocale() const
    {
        if( !pSysLocale )
            _CreateSysLocale();
        return *pSysLocale;
    }

    VirtualDevice &     GetDefaultVirtualDev()
    {
        if (!pVirtualDev)
            _CreateVirtualDev();
        return *pVirtualDev;
    }

    //virtual methods for options dialog
    virtual SfxItemSet*  CreateItemSet( sal_uInt16 nId ) SAL_OVERRIDE;
    virtual void         ApplyItemSet( sal_uInt16 nId, const SfxItemSet& rSet ) SAL_OVERRIDE;
    virtual SfxTabPage*  CreateTabPage( sal_uInt16 nId, vcl::Window* pParent, const SfxItemSet& rSet ) SAL_OVERRIDE;
};

#define SM_MOD() ( *reinterpret_cast<SmModule**>(GetAppData(SHL_SM)) )

#endif // INCLUDED_STARMATH_INC_SMMOD_HXX

/* vim:set shiftwidth=4 softtabstop=4 expandtab: */
