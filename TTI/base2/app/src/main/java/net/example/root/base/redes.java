package net.example.root.base;

import android.content.Context;
import android.net.ConnectivityManager;
import android.net.NetworkInfo;

public class redes {

    public static boolean isREd(Context context)
    {
        ConnectivityManager connectivityManager=(ConnectivityManager) context.getSystemService(Context.CONNECTIVITY_SERVICE);
        NetworkInfo networkInfo=connectivityManager.getActiveNetworkInfo();
        return networkInfo!= null && networkInfo.isConnected();
    }


}
