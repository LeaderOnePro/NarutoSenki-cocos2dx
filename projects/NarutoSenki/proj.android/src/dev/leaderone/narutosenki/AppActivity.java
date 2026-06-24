package dev.leaderone.narutosenki;

import org.cocos2dx.lib.Cocos2dxActivity;

import android.content.Intent;
import android.net.Uri;
import android.os.Bundle;

public class AppActivity extends Cocos2dxActivity {

    protected void onCreate(Bundle savedInstanceState) {
        super.onCreate(savedInstanceState);
    }

    // Open an external URL in the system browser. Called from C++ via JNI.
    public static void openUrl(String url) {
        try {
            Intent intent = new Intent(Intent.ACTION_VIEW, Uri.parse(url));
            intent.addFlags(Intent.FLAG_ACTIVITY_NEW_TASK);
            getContext().startActivity(intent);
        } catch (Exception e) {
            // No browser available; ignore silently
        }
    }

    static {
        System.loadLibrary("cocos2dcpp");
    }
}
