package com.example.cohesive_android;

import android.app.Activity;
import android.content.res.Resources;
import android.graphics.drawable.ColorDrawable;
import android.graphics.drawable.Drawable;
import android.os.Bundle;
import android.view.ContextThemeWrapper;
import android.view.View;
import android.widget.LinearLayout;

public class Cohesive extends Activity {
    @Override
    public void onCreate(Bundle savedInstanceState) {
        super.onCreate(savedInstanceState);
        setContentView(R.layout.main);

        Resources themeWrapper = getResources();

        final int flippedColor = themeWrapper.getColor(R.color.Flipped);
        final int cardColor = themeWrapper.getColor(R.color.Card);

        LinearLayout ll = (LinearLayout) findViewById(R.id.mainLayout);
        int children = ll.getChildCount();

        for (int i = 0; i < children; i++) {
            View view = ll.getChildAt(i);
            if (view instanceof StyledView) {

                view.setOnTouchListener(new View.OnTouchListener() {

                    @Override
                    public boolean onTouch(View view, android.view.MotionEvent motionEvent) {
                        Drawable background = view.getBackground();
                        int color = 0;

                        if (background instanceof ColorDrawable)
                            color = ((ColorDrawable) background).getColor();

                        view.setBackgroundColor(color == cardColor ? flippedColor : cardColor);

                        return false;
                    }
                });

            }
        }


    }
}


