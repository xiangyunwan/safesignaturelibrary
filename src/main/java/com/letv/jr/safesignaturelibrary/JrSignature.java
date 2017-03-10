package com.letv.jr.safesignaturelibrary;

import android.content.Context;

/**
 * Created by zhangzhenzhong.zhangzhenzhong@le.com
 *
 * @version: 1.0
 * @date: 2017/3/6
 * @Copyright (c) 2017. LetvFinancial. All rights reserved. Inc.
 */
public class JrSignature {
    static {
        System.loadLibrary("jrSafeSignature");   //defaultConfig.ndk.moduleName
    }
    public  Context mContext;
    public JrSignature(Context context){
        mContext=context;
    }

    public  void compareSignature(CompareCallback compareCallback){
        if (getCompareInt(this.mContext)==0){
            compareCallback.onSuccess();
        }else{
            compareCallback.onFail();
        }
    }

    public native int getCompareInt(Context context);

}
