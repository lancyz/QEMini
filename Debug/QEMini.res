        ��  ��                  t      �� ��     0         t4   V S _ V E R S I O N _ I N F O     ���                                         �   S t r i n g F i l e I n f o   �   0 8 0 4 0 4 b 0   6   F i l e D e s c r i p t i o n     Q E M i n i     6   F i l e V e r s i o n     1 ,   0 ,   0 ,   1     .   I n t e r n a l N a m e   Q E M i n i     J   L e g a l C o p y r i g h t   C o p y r i g h t   ( C )   2 0 1 1     >   O r i g i n a l F i l e n a m e   Q E M i n i . e x e     .   P r o d u c t N a m e     Q E M i n i     :   P r o d u c t V e r s i o n   1 ,   0 ,   0 ,   1     D    V a r F i l e I n f o     $    T r a n s l a t i o n     �c  8   U I D E F   X M L _ I N I T         0         ﻿<?xml version="1.0" encoding="utf-8"?>
<UIDEF>
  <font face="微软雅黑" size="15"/>

  <string src="values:string" />
  <skin src="values:skin"/>
  <color src="values:color"/>


  <style>
    <class name="cls_edit" ncSkin="_skin.sys.border" margin-x="2" margin-y="2" />
    <class name="normalbtn" font="" colorText="#385e8b" colorTextDisable="#91a7c0" textMode="0x25" cursor="hand" margin-x="0"/>
    <class name="cls_btn_weblink" cursor="hand" colorText="#1e78d5" colorTextHover="#1e78d5" font="italic:1" fontHover="underline:1,italic:1" />
  </style>

  <objattr>
  </objattr>
</UIDEF> �  @   L A Y O U T   X M L _ M A I N W N D         0         ﻿<SOUI name="mainWindow" title="@string/title" bigIcon="ICON_LOGO:32" smallIcon="ICON_LOGO:16" minsize="910,610" width="910" height="610"  margin="20,5,5,5"  resizable="1" wndType="appMain"
toolWindow="1"
translucent="1"
appWnd="1"
trCtx="dlg_main"
>
  <root skin="skin.shadow"  cache="1">
    <window pos="5,3,-5,-7" colorBkgnd="rgb(255,255,255)" >
    <caption pos="0,0,-0,30" show="1" font="adding:0">
      <icon pos="10,8" src="ICON_LOGO:16"/>
      <!--<text pos="29,5">@string/title</text>-->
      <imgbtn name="btn_close" skin="skin.sys_close_btn"    pos="-28,0" tip="close" animate="1"/>
      <imgbtn name="btn_max" skin="skin.sys_max_btn"  pos="-56,0" animate="1" />
      <imgbtn name="btn_restore" skin="skin.sys_restore_btn"  pos="-56,0" show="0" animate="1" />
      <imgbtn name="btn_min" skin="skin.sys_min_btn" pos="-84,0" animate="1" />
    </caption>
        <window pos="0,[2,-0,-0">

          <gstabctrl id="30000" tabPos="60" pos="0,0,-0,-0" name="tab_main" colorBkgnd="rgb(46,50,56)" icon-x="10" icon-y="12" text-x="56" text-y="30" iconSkin="skin.ico_table" tabSkin="" cursor="hand"
               animateSteps="13" animateType="1" tabAlign="left" tabHeight="50" tabWidth="60" drawFocusRect="0"
                colorText="#c1c1c1" colorTextHover="#5748EA" colorTextPush="#5748EA" colorTextDisable="#5748EA"  >

            <page title="chat">
              <include src="layout:page_chat"/>
            </page>

            <page title="contact">
               <include src="layout:page_contact"/>
            </page>

            <page title="app">
              <include src="layout:page_app"/>
            </page>

          </gstabctrl>

          <!--head-->
          <img pos="10,10,@40,@40" name="imgMainHead" skin="skin.icon2" />
          <!--setup btn-->
          <imgbtn name="btn_setup" skin="skin.btn_setup" pos="12,-45" animate="1" />

         </window>
      </window>
      </root>
</SOUI>
 �  @   L A Y O U T   X M L _ L O G I N W N D       0         <SOUI name="loginWindow" title="QE" bigIcon="ICON_LOGO:32" smallIcon="ICON_LOGO:16" width="390" height="304" appWnd="1" resizable="0" translucent="1" trCtx="dlg_login">
  <root>
    <window pos="0,0,-0,-0" skin="img_login_border" cache="1">
      <window pos="6,6,-6,-6" colorBkgnd="#ffffff">

		  <caption pos="0,0,-0,30">
		    <!--title bar-->
		    <icon pos="10,8" src="ICON_LOGO:16"/>
		    <text pos="[5,4">@string/title</text>
		    <imgbtn name="btn_close" skin="skin.sys_close_btn"    pos="-28,0" tip="close" animate="1"/>
		    <imgbtn name="btn_min" skin="skin.sys_min_btn" pos="-56,0" animate="1" />
		  </caption>
		  <caption pos="0,30,-0,-0">
		    <!--body-->
		    <caption pos="0,80,-0,-0">
			  <img pos="23,37,101,115" skin="skin.icon2" name="img_avatar"/>

			  <!--<img pos="22,36,102,116" skin="img_head_mask" />-->


          <window pos="114,36,300,64" class="cls_edit" colorBkgnd="#ffffff">
            <edit name="edit_empNo" pos="0,0,-19,-0" margin="0" password="0" mouseRelay="1" cueText="Employee number"/>
          </window>
			  <window pos="114,70,300,98" class="cls_edit" colorBkgnd="#ffffff">
			    <edit name="edit_pwd" pos="0,0,-19,-0" margin="0" password="1" mouseRelay="1" cueText="Password"/>
			  </window>

			  <check pos="113,103" colorText="#696969" font="size:12">Keep Password</check>
			  <check pos="230,103" colorText="#696969" font="size:12">Auto Login</check>
		    </caption>
		  </caption>


		        <window pos="0,-55,-0,-0" colorBkgnd="#ffffff">
			      <imgbtn name="btn_login" pos="|-80,|-18" skin="skin.login_btn" colorText="#ffffff" animate="1">Login</imgbtn>
		        </window>


      </window>
	  </window>
   </root>
</SOUI>
 �  H   L A Y O U T   X M L _ U S E R I N F O W N D         0         ﻿<SOUI name="userInfoWindow" title="" width="300" height="265" appWnd="0" resizable="0" translucent="1" trCtx="dlg_userInfo">
  <root>
    <window pos="0,0,-0,-0" skin="img_login_border" cache="1">
      <window pos="6,6,-6,-6" colorBkgnd="#ffffff">

	  <caption pos="0,0,-0,30">
		<imgbtn name="btn_close" skin="skin.sys_close_btn"    pos="-28,0" tip="close" animate="1"/>
	  </caption>

	  <window pos="0,30,-0,-0">
	    <text pos="30,10" name="text_name" colorText="#000000" font="size:19">莫小白</text>

  		<text pos="{0,[5" colorText="#696969" font="size:13">Emp No</text>
  		<text pos="[5,{0" name="text_empNo" colorText="#000000" font="size:13">iv301</text>

  		<img pos="-90,10" skin="skin.icon2" name="img_head"/>

  		<text pos="30,-60" colorText="#696969" font="size:13">Dept</text>
  		<text pos="[5,{0" name="text_dept" colorText="#000000" font="size:13">设计部</text>
  		<text pos="30,-40" colorText="#696969" font="size:13">Phone</text>
  		<text pos="[5,{0" name="text_phone" colorText="#000000" font="size:13">18600000000</text>

  		<imgbtn name="btn_chat" pos="-70,-60" skin="skin.btn_chat" colorText="#ffffff" animate="1" tip="Contact him\her"/>
	  </window>


   </window>
	</window>
   </root>
</SOUI>
    @   L A Y O U T   X M L _ S E T U P W N D       0         <SOUI name="setupWindow" title="" width="300" height="265" appWnd="0" resizable="0" translucent="1" wndType="normal" trCtx="dlg_setup">
  <root>
    <window pos="0,0,-0,-0" skin="img_login_border" cache="1">
      <window pos="6,6,-6,-6" colorBkgnd="#ffffff">

	  <caption pos="0,0,-0,30">
		<imgbtn name="btn_close" skin="skin.sys_close_btn"    pos="-28,0" tip="close" animate="1"/>
	  </caption>

	  <window pos="0,30,-0,-0">

	  </window>
       <buttonex pos="10,10,@63,@24" name="btn_ch" skin="skin.color_btn" colorText="#ffffff" textShift="2,1" animate="1">Chinese</buttonex>
       <buttonex pos="10,50,@63,@24" name="btn_en" skin="skin.color_btn" colorText="#ffffff" textShift="2,1" animate="1">English</buttonex>
      </window>
	</window>
   </root>
</SOUI>
  �   P   L A Y O U T   S E L E C T I O N D R O P D O W N W N D       0         <SOUI width="172" height="172" translucent="1" >
  <root skin="skin.shadow">
    <window pos="6,6,-6,-6"  colorBkgnd="#ffffff">
      <listboxex name="selectionlist" pos="0,0,-0,-0" itemHeight="20">
      </listboxex>
    </window>
  </root>
</SOUI>
  �  <   L A Y O U T   P A G E _ C H A T         0         <include>

  <!--最近联系人列表-->
  <window pos="0,0,@250,-0" colorBkgnd="rgb(229,229,229)">
    <listview pos="0,0,-0,-0" name="lv_user" dividerSize="5" wantTab="1" sbSkin="skin.common.vscroll">

      <template itemHeight="50" trackMouseEvent="1">
        <itemEvenNormal colorHover="rgb(220,220,220)" colorSelected="rgb(206,205,203)">
          <img pos="8,7,@40,@40"  name="imgHead"  skin="skin.icon2" />
          <text name="textName" align="left" font="color:#000000,size:14,face:微软雅黑" pos="[5,8">风满楼</text>
          <text name="textDate" pos="-10,25" offset="-1,0" colorText="#A9A9A9" font="size:13">2-28</text>
        </itemEvenNormal>
        <!--
                <itemEvenHover name="lv_item_hover" colorHover="#E5F0FA" colorSelected="#F8F8FF">
                  <imageMask name="head_user2"  pos="20,7,@35,@35" skin="skin_head30" mask="IMG:ID_ICON_MASK30.g" show="0"/>
                  <imgbtn name="tab_btn_del" skin="skin_tabbtn_close"    pos="0,15" tip="删除" animate="1"/>
                  <imgbtn name="btn_call" skin="skin_btn_call"    pos="50,0" tip="语音" animate="1"/>
                </itemEvenHover>
                -->
      </template>
    </listview>
  </window>

  <!--聊天区域-->
  <window name="wnd_chat" pos="[0,0,-0,-0" colorBkgnd="rgb(245,245,245)" show="0">
    <!--消息接收框-->
    <window pos="0,0,-0,@410">
      <text name="textUserName" colorText="#000000" font="size:16,face:微软雅黑" pos="15,5" >莫小白</text>
      <hr size="1" colorLine="#ced9e2" pos="0,40,-0,@1" msgTransparent="1" />
      <imrichedit name="re-message" pos="0,[0,-0,-0" bkgndBlend="1"  enableDragdrop="1" readOnly="1" autoSel="0" multiLines="1" autoWordSel="0" vscrollBar="1" wordWrap="1"  autoVscroll="0" hscrollBar="0" wantReturn="1" scrollSpeed="60" inset="5,0,12,0" sbSkin="skin.common.vscroll"/>
    </window>

    <window pos="{0,[0,-0,-0" colorBkgnd="rgb(255,255,255)">
      <hr size="1" colorLine="#ced9e2" pos="0,0,-0,@1" msgTransparent="1" />

      <imgbtn name="btn_face" skin="skin.ico_face"   pos="5,2,@20,@20" tip="表情" animate="1"/>
      <imgbtn name="btn_sendpic" skin="skin.ico_sendpic"    pos="[5,{0,@20,@20" tip="发送图片" animate="1"/>
      <imgbtn name="btn_cut" skin="skin.ico_cut"    pos="[5,{0,@20,@20" tip="截图" animate="1"/>
      <!--消息发送框-->
      <imrichedit name="re-input" pos="0,[2,-0,-40" colorText="#000000" bkgndBlend="1"  enableDragdrop="1" autoSel="0" multiLines="1" autoWordSel="0" vscrollBar="1" wordWrap="1"  autoVscroll="1" hscrollBar="0" wantReturn="1" cursor="" sbSkin="skin.common.vscroll"/>

      <!--底部按钮-->
      <window pos="0,-30,-10,-0">
        <!--
        <buttonex pos="-167,0,@70,@24" skin="skin.chatbtn_close" colorText="#ffffff" textShift="2,1" animate="1">关闭(C)</buttonex>
        -->
        <buttonex pos="-93,0,@63,@24" name="btn_send" skin="skin.color_btn" colorText="#ffffff" textShift="2,1" animate="1">Send</buttonex>
        <img      pos="-31,0,@2,@24"  skin="skin.send_btn_split_line"/>
        <buttonex pos="-30,0,@26,@24"  name="btn_showsendmenu" bkgndSkin="skin.sendbtn_right" skin="skin.send_btn_arrow" animate="1"/>
      </window>
    </window>

    <!--face wnd-->
    <window name="wnd_face" pos="{0,210,@500,@200" skin="img_login_border" cache="1" show="0">
      <window pos="6,6,-6,-6" >
        <tileview pos="0,0,-0,-0" name="lv_face_tile" wantTab="1" marginSize="5" colorBkgnd="#ffffff" colorSelText="#FFFFFF" colorText="#FFFFFF" vscrollBar="1" sbSkin="skin.common.vscroll" wordWrap="1"  autoVscroll="1" hscrollBar="0" show="1">
          <template itemHeight="32" itemWidth="32" trackMouseEvent="1" colorHover="rgb(235,235,235)" colorSelected="rgb(206,205,203)">
            <img name="img_face"  pos="|-14,|-14" show="1"/>
          </template>
        </tileview>
      </window>
    </window>

  </window>

  <text pos="|0,|0" offset="-0.5,-0.5" show="0">这是一个由SOUI向导生成的APP框架</text>
  <button pos="|0,[" inset="4,4,4,4" name="zh_cn" offset="-1.1,0" text="lang_cn" show="0"/>
  <button pos="|0,[" inset="4,4,4,4" name="jp" offset="-1.1,0" text="lang_jp" show="0"/>

</include>
 �  @   L A Y O U T   P A G E _ C O N T A C T       0         <include>
  <!--联系人列表-->
  <window pos="0,0,@250,-0" colorBkgnd="rgb(229,229,229)">
    <listview pos="0,0,-0,-0" name="lv_contact" dividerSize="5" wantTab="1" sbSkin="skin.common.vscroll">

      <template defHeight="50" separHeight="30" trackMouseEvent="1">

        <itemUser colorHover="rgb(220,220,220)" colorSelected="rgb(206,205,203)">
          <img pos="8,7,@40,@40"  name="img_head_user"  skin="skin.icon2" />
          <text name="text_user_name" align="left" font="color:#000000,size:14,face:微软雅黑" pos="[5,8">莫小白</text>
        </itemUser>

        <itemGroup colorHover="rgb(220,220,220)" colorSelected="rgb(206,205,203)">
          <img pos="8,7,@40,@40"  name="img_head_group"  skin="skin.icon2" />
          <text name="text_group_name" align="left" font="color:#000000,size:14,face:微软雅黑" pos="[5,8" >风满楼</text>
        </itemGroup>

        <itemSepar colorHover="rgb(220,220,220)" colorSelected="rgb(206,205,203)">
          <text name="text_title" align="left" font="bold:1,color:#000000,size:14,face:微软雅黑" pos="[70,5" offset="-1,0">分隔符</text>
        </itemSepar>

      </template>
    </listview>
  </window>

  <window pos="[0,0,-0,-0" colorBkgnd="rgb(245,245,245)">
    <!--个人信息-->
    <window name="wnd_user_info" pos="0,0,-0,-0" colorBkgnd="rgb(245,245,245)" show="0">

      <text pos="100,100" name="text_name" colorText="#000000" font="size:19">莫小白</text>

      <text pos="{0,[5" colorText="#696969" font="size:13">Emp No</text>
      <text pos="[5,{0" name="text_empNo" colorText="#000000" font="size:13">iv301</text>

      <img pos="-200,100" skin="skin.icon2" name="img_head"/>

      <text pos="100,[5" name="text_note" colorText="#696969" font="size:16">签名</text>

      <text pos="100,300" colorText="#696969" font="size:13">Dept</text>
      <text pos="[5,{0" name="text_dept" colorText="#000000" font="size:13">设计部</text>

      <text pos="100,[5" colorText="#696969" font="size:13">Phone</text>
      <text pos="[5,{0" name="text_phone" colorText="#000000" font="size:13">18600000000</text>

      <imgbtn name="btn_chat" pos="-70,-60" skin="skin.btn_chat" colorText="#ffffff" animate="1" tip="Contact him\her"/>

    </window>

    <!--群组信息-->
    <window name="wnd_group_info" pos="0,0,-0,-0" colorBkgnd="rgb(245,245,245)" show="0">

      <text name="text_group_title" colorText="#000000" font="size:16,face:微软雅黑" pos="15,5" >风满楼</text>

      <tileview pos="50,30,-45,-100" name="lv_member_tile" wantTab="1" marginSize="5" colorBkgnd="rgb(245,245,245)" vscrollBar="1" sbSkin="skin.common.vscroll" wordWrap="1"  autoVscroll="1" hscrollBar="0">
        <template itemHeight="99" itemWidth="70" trackMouseEvent="1" colorHover="rgb(220,220,220)" colorSelected="rgb(206,205,203)">
          <img pos="5,5"  name="img_head_member"  skin="skin.icon2" />
          <text name="text_member_name" align="center" pos="0,[5,-0,-0" colorText="#696969">莫小白</text>
        </template>
      </tileview>

      <imgbtn name="btn_group_chat" pos="-70,-60" skin="skin.btn_chat" colorText="#ffffff" animate="1" tip="Send message"/>

    </window>
  </window>

</include>
     8   L A Y O U T   P A G E _ A P P       0         <include>
  
  
</include>   �  D   L A Y O U T   F I L E O L E L A Y O U T         0         <root>
  <window pos="0,0,-0,-0" skin="skin.rich_file_bk">
    <img name="ImgFileIcon" skin="skin.file_icon_text" pos="10,10,@40,@40" cursor="hand" />
    <text name="LblFileName" skin="skin.empty" align="left" font="size:12" pos="55,10,-10,28" cursor="hand"/>
    <text name="LblFileSize" font="size:12" colorText="#808080" pos="55,30,-10,50"/>
    <hr pos="0,65,-0,66" size="1" colorLine="#ced9e2" />
    <window name="WndLinksContainer" pos="0,[0,-0,-0" >
      <link name="LnkOpenFile" pos="]-5,|0" offset="-1.0,-0.5" class="cls_rich_link" display="0" visible="1">打开</link>
      <link name="LnkOpenFileDir" pos="]-5,|0" offset="-1.0,-0.5" class="cls_rich_link" display="0" visible="1">打开文件夹</link>
      <link name="LnkContinueFile" pos="]-5,|0" offset="-1.0,-0.5" class="cls_rich_link" display="0" visible="1">继续</link>
      <link name="LnkSaveFile" pos="]-5,|0" offset="-1.0,-0.5" class="cls_rich_link" display="0" visible="1">保存</link>
      <link name="LnkSaveFileAs" pos="]-5,|0" offset="-1.0,-0.5" class="cls_rich_link" display="0" visible="1" >另存为</link>
      <link name="LnkCancelFile" pos="]-5,|0" offset="-1.0,-0.5" class="cls_rich_link" display="0" visible="1">取消</link>
      <link name="LnkForwardFile" pos="]-5,|0" offset="-1.0,-0.5" class="cls_rich_link" display="0" visible="1">转发</link>
    </window>
    <text name="LblState" font="size:12" colorText="#808080" pos="10,70,100,-5"/>
  </window>
</root>
 �  L   L A Y O U T   S E P E R A T O R O L E L A Y O U T       0         <root >
  <window name="parent" pos="0,0,-0,-0">
    <hr pos="|-112,9,@30,@1" size="1" colorLine="#d7dfe8"/>
    <hr pos="[0,9,@35,@1" size="1" colorLine="#c6ced7"/>
    <text  pos="[5,0" colorText="#808080" font="size:12">以上是历史消息</text>
    <hr pos="[5,9,@35,@1" size="1" colorLine="#c6ced7"/>
    <hr pos="[0,9,@30,@1" size="1" colorLine="#d7dfe8"/>
  </window>
</root>
  �   D   L A Y O U T   I M A G E O L E L A Y O U T       0         <root>
  <window pos="0,0,-0,-0">
    <image name="player" pos="0,0,-0,-0" />
    <!--<imgbtn name="BtnManifier" skin="skin.tabbtn_close" pos="-18,-18,@16,@16" />-->
  </window>
</root>
  �  L   L A Y O U T   F E T C H M O R E O L E L A Y O U T       0         <root >
  <window name="WndParent" pos="0,0,-0,-0">
    <window name="WndFetchMore" pos="|0,|0" offset="-0.5,-0.5">
      <img name="ImgIcon" skin="skin.fetch_more_msg" pos="0,3" offset="-1.0,0"/>
      <link name="LnkFetchMore" pos="[5,0" class="cls_rich_link" >查看更多消息</link>
    </window>
    <window name="WndOpenHistory" pos="|0,|0" offset="-0.5,-0.5"  visible="0">
      <window name="WndNoMoreMsg" pos="0,0" display="0" font="size:12">更多消息请在消息记录中查阅，</window>
      <link name="LnkOpenHistory" pos="[0,0" class="cls_rich_link" >打开历史记录</link>
    </window>
    <image name="ImgLoadingMore" pos="|0,|0,@16,@16" offset="-0.5,-0.5" visible="0" />
  </window>
</root>
�   L   L A Y O U T   R E M A I N D E R O L E L A Y O U T       0         <root>
  <window name="parent" pos="0,0,-0,-0">
    <text name="LblText" pos="0,0,-0,-0" dotted="1"></text>
  </window>
</root>
  L   L A Y O U T   M E T A F I L E O L E L A Y O U T         0         <root>
  <windowex name="WndParent" pos="0,0,-0,-0" cursor="hand">
    <img name="ImgFile" pos="|0,5,@40,@40" offset="-0.5,0" msgTransparent="1"/>
    <text name="LblFileName" pos="5,[5,-5,-0" font="size:12" dotted="1" msgTransparent="1" align="center" />
  </windowex>
</root>
  z   4   V A L U E S   S T R I N G       0         ﻿<?xml version="1.0" encoding="utf-8"?>
  <string>
    <title value="QE mini"/>
    <ver value="1.0"/>
  </string>
  �   4   V A L U E S   C O L O R         0         ﻿<?xml version="1.0" encoding="utf-8"?>

<color>
  <red value="rgb(255,0,0)"/>
  <green value="rgb(0,255,0)"/>
  <blue value="rgb(0,0,255)"/>
  <white value="rgb(255,255,255)"/>
  <gray value="#808080"/>
</color> 
   I  0   V A L U E S   S K I N       0         ﻿<?xml version="1.0" encoding="utf-8"?>

<skin>
  	<imglist name="skin_traymenu_icons"	src="img:traymenu_icons" states="9"/>

    <imgframe name="img_login_border" src="img:IMG_LOGIN_BORDER" left="9" top="9" right="9" bottom="9"/>
    <imgframe name="skin.shadow" src="img:img_shadow" left="5" top="3" right="5" bottom="7"/>

    <imgframe name="skin.rich_file_bk" src="IMG:ID_RICH_FILE_BK" left="14" top="20" right="14" bottom="20"/>
   <imgframe name="skin.file_icon_text" src="IMG:ID_FILE_ICON_TEXT" />
   <imgframe name="skin.menu_bkg" src="IMG:ID_MENU_BKG" left="10" top="10" right="10" bottom="10"/>
   <imgframe name="skin.empty"	src="IMG:ID_EMPTY"/>

    <gsimglist name="skin.login_btn"	imglist="img:btn_login_normal;img:btn_login_hover;img:btn_login_press" states="3"  />

    <gsimglist name="skin.sys_close_btn"	imglist="img:sys_close_normal;img:sys_close_hover;img:sys_close_press" states="3"  />
    <gsimglist name="skin.sys_max_btn"	imglist="img:sys_max_normal;img:sys_max_hover;img:sys_max_press" states="3"  />
    <gsimglist name="skin.sys_min_btn"	imglist="img:sys_min_normal;img:sys_min_hover;img:sys_min_press" states="3"  />
    <gsimglist name="skin.sys_restore_btn"	imglist="img:sys_restore_normal;img:sys_restore_hover;img:sys_restore_press" states="3"  />

    <imgframe name="skin.icon2" src="img:test_icon2" />

    <imgframe name="skin.send_btn_split_line" src="PNG:ID_SENDBTN_SPLITLINE" />
    <imgframe name="skin.send_btn_arrow" src="PNG:ID_SENDBTN_ARROW" states="3"/>

    <colormask name="skin.color_btn" colorNormal="#069dd5" colorHover="#4bcaff" colorDown="#069dd5" colorDisable="#069dd5" width="252" height="24"  mask="PNG:ID_SENDBTN_LEFT.a"/>
    <colormask name="skin.sendbtn_right" colorNormal="#069dd5" colorHover="#4bcaff" colorDown="#069dd5" colorDisable="#069dd5" width="128" height="24" mask="PNG:ID_SENDBTN_RIGHT.a"/>
    <colormask name="skin.chatbtn_close" colorNormal="#069dd5" colorHover="#4bcaff" colorDown="#069dd5" colorDisable="#069dd5" width="280" height="24" mask="PNG:ID_CHATBTN_CLOSE.a"/>

    <imgframe name="skin.rich_warning" src="PNG:ID_RICH_WARNING" />
    <imgframe name="skin.rich_left_bubble" src="PNG:ID_RICH_LEFT_BUBBLE" left="15" top="19" right="15" bottom="19"/>
    <imgframe name="skin.rich_right_bubble" src="PNG:ID_RICH_RIGHT_BUBBLE" left="15" top="19" right="15" bottom="19"/>
    <imgframe name="skin.rich_sysmsg_bk" src="PNG:ID_RICH_SYSMSG_BK" left="9" top="9" right="9" bottom="9"/>
    <vscrollbar name="skin.common.vscroll" src="PNG:ID_DEF_VSCROLL" states="1" margin="3" hasgripper="0"/>

    <gsimglist name="skin.ico_face"	imglist="img:face_normal;img:face_hover;img:face_press" states="3"  />
    <gsimglist name="skin.ico_sendpic"	imglist="img:sendpic_normal;img:sendpic_hover;img:sendpic_press" states="3"  />
    <gsimglist name="skin.ico_cut"	imglist="img:cut_normal;img:cut_hover;img:cut_press" states="3"  />

    <gsimglist name="skin.btn_chat"	imglist="img:chat_normal;img:chat_hover;img:chat_press" states="3"  />
    <!--tabSkin-->
    <gsimglist name="skin.ico_table"	imglist="img:chat_normal;img:contacts_normal;img:app_normal;img:chat_hover;img:contacts_hover;img:app_hover;img:chat_press;img:contacts_press;img:app_press" states="9"  />
    <gsimglist name="skin.btn_setup" imglist="img:setup_normal;img:setup_hover;img:setup_normal" states="3" />
	</skin>
   0  @   I M G   T R A Y M E N U _ I C O N S         0         �PNG

   IHDR   �      9S?   tEXtSoftware Adobe ImageReadyq�e<   iTXtXML:com.adobe.xmp     <?xpacket begin="﻿" id="W5M0MpCehiHzreSzNTczkc9d"?> <x:xmpmeta xmlns:x="adobe:ns:meta/" x:xmptk="Adobe XMP Core 5.0-c060 61.134777, 2010/02/12-17:32:00        "> <rdf:RDF xmlns:rdf="http://www.w3.org/1999/02/22-rdf-syntax-ns#"> <rdf:Description rdf:about="" xmlns:xmp="http://ns.adobe.com/xap/1.0/" xmlns:xmpMM="http://ns.adobe.com/xap/1.0/mm/" xmlns:stRef="http://ns.adobe.com/xap/1.0/sType/ResourceRef#" xmp:CreatorTool="Adobe Photoshop CS5 Windows" xmpMM:InstanceID="xmp.iid:50FEEA721B3611E1B3C7853228C20ABA" xmpMM:DocumentID="xmp.did:50FEEA731B3611E1B3C7853228C20ABA"> <xmpMM:DerivedFrom stRef:instanceID="xmp.iid:50FEEA701B3611E1B3C7853228C20ABA" stRef:documentID="xmp.did:50FEEA711B3611E1B3C7853228C20ABA"/> </rdf:Description> </rdf:RDF> </x:xmpmeta> <?xpacket end="r"?>���<  ,�IDATx�\{�$�y�7�=ݓ����.�w8�C � 	
�J2��AV�,�t�U�\�6]rI�K�T6iɲL�L�� x p8�rڻ�y'��=�3=�^/AS^స	o�����o����ǿ>6>1�H@�+��p�m
h�]t-���A��^��ۃ���7;|����׿���r���+?����N���7����X=���q�E�o�>��>������}�w}^o��'9�����X�\��Qe'|�
���qz|\�8W�F��ǃ6���l���7U���/���nLv�|�f���_C����1d��ۅ[�(1O�� �ɴ��7��-��Wz��W���zĜñ>�It�:��<����i��z�z*�j3F.ͅ����o����>��#����N۔Ě�.MC����$�E���8�� Fg�r�/�Q�N\������h��Ç}�s��s���z��H"���\�K����q�:-H�
EVp����wϿ�O�l�ч��3��o&dI�����\�����䦋�e�oe�^���ےCj<p��9rN��L��Y��oس��*�b�U�H$>&� �._����G���<�������y�s�`P�1���?�Sf>�g��c��7p�N\�|%y���+˲��ϼ�'��xBa�88V��9w��<��9	�zm?9E^+"�C�������7���v�~�W����wj�Ё�s� 5݁��+��=1[�7���#½���/�ǿ�8y��ۆ�9�p���g�x��L�U2�pˁ��QL�ġ�C�706���!�#��W6Pl�������i6k���յՏC`�_$��Ay�i0[-4�=�V���E�O>��7n�~��}���Óʟ����vP���G���,l�N!���B�?
ɥa
��f�&�n��O�zf�x2�E���k��P�s.��.�!W�ل*�k��EKqb >�b����I��ßy>�r�������G����K�<�����_�{�#�q�
���|j��",ˁ�ő�~l/^����G�y�Nlc}m�������Hd�Ć�p��/�a�;do�䀊��6j���f��K�e�۵_?�`,�C��b��P�p]V]��A4�#�z���K���8����a�4��ė�\��P:���Bv�<,��Ä
��yuZmƫ�f>��a��8y�$L���l6w�����bQ>��gbb��. �ɇ���d�����mw��U�s�h޹���`p�e�����_`���@�Y&�qn���bcޘ����p�0�V���������;Gy�/�/��C�>LM�A�*��s��ڭ\	�SaF���|���aay���{��~qxz:Z�����&|K[�k�q�h=0��/ep�fU�I�P�s��{�5�8�#�F�NA{磿���ȍ�F�.��∸���,a��<vG�Oahr�X{+H,��qFۉｻ.�"r��%��l��?:�L�m<�0�7��:�<�v�������676�[�e8咵�L�C�%��çp(�Ot�"`��"��T.Ώ�t�;I�%�5u��ug����|�^㚎,��J������a<;��i2_Ɋ�^;:ќ@P�fX����s�ݪNO�D!�B(֏Zn�k���W��3O2��p�E�7��FQ-�`��Ɔ���k[q��5ۆk��B,����A"�ɉQ�!v��j�U8�������$7��ɒ��<��Sn���-.����ボo���j2�-����4C}����Y[A2����[0:֡����[�}k�3ҏ�s�?�Gz�g031�t��lS�Ăm��&���Q-ѨV����H42Mv9w��]���a��������9s'^}	c<�&;Z��p�ak�z�&lOo`ikK�ܡx<z�G�����!7>��N?F1kb}�ǹTQ�� ��Zc�t�d�������Ɍ������=p��bbh���$�'�0���5�c^�I��4�0�Ho��Ӭ���뎎��ŇnK���A�^��^z_o� ���nJ�������><q��n���gQg.dJ�bmZ�d�#���y�Lf�Dyg���� ��0�����Ϗɳ'�uk��pxڇ��WȈ��4��e!7m>��4�K-l�[dʚ��S�4n1�D'ѓH�r:\���K�?���C:v%L�ƙ�n���r�H�?����p'Q��"],��:���;���&I�q�H��)�Fe �����H�I5q����mm`ag߹�>��4b3�0-��\���Aa��Q/���$0{� ��I�kU��UB�V���G%����tQFX����D@�[ZB�	����Ș�p���H1��x�B͖Hz=����X�s�r��ui�����J8��_x�e\É��Nb~,���*�$e��r�����H�%)m3,�
�>��L&�p�?�Y��>��H��P����B�R���khVp�\K�~��,R,�^��V�ղ����cp��� ���g����}�����kWm�AJ���G�:��w�/�Ub�����2i%��U����+�x�	�NT�X|dӵ�*�Rg,8O�l+$`��r���p#����u��Fj��`|��	JC�=�`$_C&YE�x^��B�A�����[7�{V�et� |�*��؍��l�x�D�����ﬡ�HZX��2��+A�d`������i[J�H��qj&��tF����K����4�����b���`�C�֛X������U()U��R=�8�/!ͪ�Q�I|�����TU��f��.N�ӧ�۟Y���F���S��R�N'0:6d��R��խ]���
��&�L��3t���Q*�s��Cq�`pԍ���Xo��)�XUK0 )V���'��ibn� &;�mud��������=7�|�����8Gf�vk.J���=��U�`���.��aX)���-�7I6qCL\/�nvv�0(S�s�=�(���[(e��Q�}c��^�u*|U����1x��'����e�5p�Ë�O_}B9z�@��N��5��0ʅ��]�ZLVE��rQ�4�:AHC�R�̡C�]
��]�X����P��ɠ~�n�W5����(on۞������ۘ�=���&0�ѫW���{̭ �����0{p7�G~]gA�s�����X��e�\�y����q�Y�`�V7����3P*H���C��L���&揺��b��M[��U�.g���ԅ_�l����C�ܮ"�S�5Ɩ�g*E��ֽ�s���l�L��m�b)���'Ǳ{� ������}��?�a��a\��w�(��GtW13-㌲��f�0~�q"�V�X\���>�} �ۋ{X�4�Vj"��܁����q��i��mID������Xģ��A��	ԣ��`.6��Q��'���;��{EJ�A_���N�;���?�ȑy���o�^�6�D��!|���� "�Q��2�eY0L^P���A`]��q��ǜx�e���zR�����%\�_E��#xl�����@��OWr �����f"�f��|��"�Q�����+ٝ��	L;v��1�h���,��c����dQ0�I J��151�o���(�(�Ɯ����\�EQF�ؾ�!\s����������;o�;x�C,�*d�Ω�1Jy�
=���?��b��QE��Okk0�U|�K_F6��˯�<�]��Z�r�G�~�C	�j�} ��򄂨�N����c���aU;+kp4{d�]�%�(��;�l��VÐΐ�{�0�{kvKd���]���u��,���Dv4��F�v�*A�a�NT/��ҢT���x�+���sTz(�hWt4[)��e�(=�?�d7Y�� 
���j�R�����\��8kc��-(E)7����ŝ��tw����F�sY�yP<_���kED/^@R0��Aщ������\���������$M���qe�)���i-n�1<�;z����(y$ʧ:5.�2��;חm6��Y�>|4�7w�L(y{����������@?����R"�_�f(g�"�|���}�6���[��,VP*��b6Z�]O���.llU7�%��6��s/`�z9ye	�}���@�M5=����,����F*�ef8�LNm���l`ky	_�s��~�,�jc��Mܾ�Cn��":���S�ҵ�M�;�Q;�\̈��A<�s���v�V�j���b�N-+�pd��t�l_�Q0L�i��x<��'��'��Y=�׏���@�Lu��uQʙ��V�FB���x�ǅu�Ѣ����]B*+��K�Ǳ�'Ҩ;L|�q�ߛ�3�&�m	[�V��!mP�:��Ҽ�r-$�����c��6y�%d�y&p\4�]*9H/����hZ��A��&~K���k��.�w�'�̨&"�
�lQ�S(�,�&'�F%�Dn�c���}�g�4(۫�\�Qb�E�G�Yǽ�E��{���n���^?:��,A��*J� 2r�D�c`މ�^�^k�V008�%�����\5{��Q6`�S1���ᾧƠ�ѧ��7c!	��-89?��h�2j�x�~z��A����w�2]7�c����o��Dk�g�`D�.۠Tiӌ*j痮�EF���N�!Y��O�i�M��6}���I?Ä߼vG��i�S8��q$����&�������'�A ��Ҫ-�mю��T"=X�&Zf��Z�GcN�����W��j��S!����&�pq�6v�52f�FDXhS���&�����7�Fp	+�o�d������|��3(�<"�'�ҩ$�TE��A�Х4I��\����;1L�� 0�=��3)��M�6����YLO?t�L�w���.��f3x���8u`�
�4c�E��>�����5$�:����1�ѵP7�u'�8����ħ��Y�o^g`%Ud��m�bR������1�^/92}�O�B�+@��v{|v����O�A6/rMJ�D*/��>�L��p_yօ���v�E�jSJ��ph8t ����E��9�^GT�b}��:?�ǂ�:��M��4�S
H�$D	G'bpHӳ����$�����RY]�v�)g���(I�` 2GR�w�٫#������{TC�Sz���5t���g�ui	�o0ۻ�|l�-hê�mmWz8�T=�^43�v�� e-Bj⡱8*�6��fיT|!���M["�~���E�!l� ����8�45uuG���==��L�Q�!���ԑ��uN"�ߏ'$$�I��:|�ٳ�� 
llb���12�݅-���#�[�Bu$�U�Ͽ�h � ���F�%Y4�$B���=jr��d�I
�N�P"a�q �A��K7��X�,L��ō���nP��U^���)�.,���~��+a��:��D���ޟ?�.��-�i�.6�f�_"�wi�#��UA������,
��C��1�/b���c��Q�Y��s���}�$�������ҙ<��k�ѽ�5�w�2����,8u=>ޡ�J��nV���WJ�H��E�hs��z��aZ`��c�J�z}x��W1;;�2����\�w}�L�8j�nk��>��ҫ����ߢ�h�r�5)��p2W�d�Z6KV�bm�.��I� ��ф/7m|�O��O���)�;	��N�q��2��:��}*q]aqw`R�W�2�Ң5�G[P���p���p3_&г;}���:ٯ��0�n�ч2ǽ
>����ܧ��Q�,_������0$J��� ��� ��*�ƃ�^�_��oa�B�EFV7`��	�#(*R��OA�$L�:uv��F��@(v�<�QG�@���� ��Ţt�hMi�����jQ6Y�#L6�e�13?�iEE��&$%��@gƆqk3K�X��joq�'���3����#���h�F
�D{��38r���1�� )��l�1��vq|��6e�>J��P5OM&�̹����v�Q�a��X%5H�e�;�MXz	*5���Q������S?�@���<��	d6n����a�Ru�~�螉��(xI����Z�j�`
�Ro�D�\��CPp
��A/�1�i�GCX��K��ZP��m�M��Kg�0X�#�	hn������Q��e�
�m���Db0���{%��VD�:���=�J�����k8z�1��&&F�x�����>��8z��C�WRMF� (�}����c|�V٭Ut�MWz-:מN�p��-��G%VU��!;�.��J�]�?��Y�T�Qƺ�>��),/V��Ʃe�[�F�W)�Ї��n��8�	Pgw��Rs���("�=��,�~К�>w	�.K�uw�Rib���}�H{0iĥ�s�x�>e��s���\��g�G��ho�Z8����{���u�7%N��ߤ��{pj�� Rr>�D�.��z[Y�ք:�C%�A�簩]hs��]\b�cNI&��Ps�Lp�ζ�Mk�P�ȝ�$�k�,�z���gC���^&��L�HV}��O#���?>��{�������µ�4��DV��J��H� �W��M��Zp����,���LiʕA�L���W��#�"Ql瘼��{4.Bg�4��!��G��iFo��<��2+{��UA��c�x�#��dѺ'��+�2]���k�(���F���Pr	fRY$:�m�W��q�ox�VS�m�#cX[I�79X,�J	z��_K\�a�Y�RA�ɲ��B�"K��r(�7�Y[�1?(˻�.٨��tc�l���$�qh~��J�g��3�O�s�ޠ�޳���w}e�ݾ�!�� ��7�-:��q��d$�@���B�Tx�]L���4�Z�=iɖ�Ŵ���Y�_?b��m�!J�vvJ������b��叠�ۥ�)�ѨH\����Dn��}� ���m���A�V�-r����\�a�E�\�ZD����M��}1�M$���37k���&��wa�� ��ڌ��ĐY�#:�``ĉ�� I_���"c	M<z܇o��D_̋�0��$��P>:��eH��L.�����2��AW7$4��Nd���%<vZ�z�f���&��(�m��C�,󱚸V#簓-ئ���Q9�d:�/��o�<s���=�n�pg�����\����D�����͜}6&�'u)�4���=�I�W�8�7E�\�7�� �غ��|
}���*�� ���2p��d�Q�z!Ř$l���Z���<�����>X�e���}��k�}�,��k��J��z�X�����sw��F���� ��F4��9����~��(�8�Ҁ}cI%��M���b��3��0��{O�{�;��G)��ӛ%�:
�٫���)��,''�\7�X]]�{�v�%`�fq�샶'�������j���>��Y�]����m0�@b���X'�����$X�f�q��h��
�g�08G�S�Рǔ˻���%��� v�޽nޭ��]�h��ד�{Xp~��n'ŵs���G�χ�u��"N��mY|,���*U�+v{;E8���/n��bXH�i�R��j�����;x�Uz>��.���2�$�Z�B��F~�9�¼�F	���!h�[L"��B��"[T(��t �n��D�Iu�`�����f���DGj���������Q�ش�-~�B������LpQnC�,�[�m qS���)�(�$/��:C��D���������9<���)΅ϥVХ�QHQ%2�k����nI��?2e��q L����UH����<BS�PG�e\^��bt`���W��L�L3��'�%[1��02�.��&�ww�d��̅��a,�<+dH��a��z �Q�Ӱ�@`_�d�� ��µk�1:4}�P�2}����u�N�a��3�`�F��߻���.¡��5���fƙ���v)p3&� �s7�}t�޶I�䡷����"ԯ�we�OxD�(n,.�h���s�#��h���j��.e�h �c!�X9��ݮ�c�Qڋ<nml��O�K։�<��%�C�k�m�dY?�U��2i��*�R(ȶ�U]��.V��9��V����C"������W���G��w/i���������L�y���F ������^T)�nm��@{�y�ޣg᪚l{fV,$�Lk�������cՀ��Z�6���%$Ny��[�[i`���,����x�ENp8�)�c�We�81��]ō킎47�?($+��k#����e���鬉#�.\N¾�:�6Q4hN��}��#^�3��VZ�fo��A̎&��:��Ql2&c�B���~漺�M]K�?�i�{�;G�����6+�v�h�r	�����Gqy�	#:�^����c�A-L�SRy���j�!@Ñ��\c�~2˽Av�Ѧ4R��Z�}A���
�`q�%���e�D�n1���6B!��'�zjzj���	��z͖YN��6��2���(������c�39��(:%�N���ۘ����glз�dl�X2�&.N_a�Y,TC|�/YUSD��{wDT���lv1��$�*�2פ�P���'�a!88��xf9�L���>��]�X��Z�,�c!�	Z���D�;��ƽ�P\�^J���Q���p��	z*�Y�;�M���NLa�~�d�$Y��N�/wX�d)�j�����ce2�N��1\�6��+	s�{U�&
�`Yt�b��3���zJU��r���'��~��ĥ�=T���r�e<u��-�o�}-T\06�tr���W�i:���z���(Tu�T��jX\�P��D`��T	�4c��D�X�i��`���>vR^Q&��ܚ8h��jq�z+K߰c���`zϾ]�R�/#���1��6�1̞��7����PʙD�:<R��R�	Ƿ�U{���_U}��������G��Kj�� Y�+n/�tjtk;y�r�Ƿ�-1���D#��Ĭg����n1�d�qC;XH��Ay���s8������}�Mk1�HR�6[d%?�A��9�~nh.���x�}(e))�yT3�hK�^������?��K���7��Mn��=c5>9C�����t��s��C��Ʃ��d�V�������9m$F�d���x����R�b�0�::ű�ʤ?"�Y}|N#����GG�aQT����{����]3��������(6���$y�YؕZվ�#���(�p*�2\��b��L�iɃ�'�,��/Rx#hn�(XW����r݆�h#,γ�����V�kb���o��WC_X(�F"�}�@\�
k��k���	d����Y+�d� �����K�?8L`�a��P\�Ћ�a�{<��	DG�0�El��f3�����.�P�F�m����q�{�Az���mD�Wk��"��dG�5[�O�1��NW	��\��f<�a0(c$�E(��_�����.�I�%n#Tk�^��Xr�il��������q�:
����Txh�s��2.�u�y#L�e�h�H�CQEd���ѱa��?��e?
�*���ܐ��S(R�
���������jeY'�@�@X
ڇ�ޑ�]d;�,�q�m�������yD�n<}�0���}W�z��^�N_��qmm����l601��d�>OA8�`�s�tj9��{]�{'��,�ɠr{��X�oGY�M�dqB$�`��!�w���;7J��a�V���
w]#x��]kr_tεet�  �Wy�Lqz�a��D�fmh��|�Lj�<U4K�2�)n���0&f���g_�3|��bwo�����q�R����t&G��a�z]4{ė�l�Wa�&���!d�[C�-,z�٫�����e�Ȯ�,��誊�9���nL�a��R�awy������@�R~�c��0���;�7��5�w�-+�}���5�V){)���l,���۸GO���D5!�p�^3<�A�ڣDя9��!<��}E�������6�$�N;�Zƍ$����`�s�}�R	*�C�t��x� ��"�bW���w���ӑ��3���͈
�S�����%�T��^���_w��(U�_\C��3���tՉ�m	;{iZ��bB�0-'���ژl	�e�H?=U�B��o��vR$�8�u{<x������c�l ����Z����xa�Fײ� *N�HH4T�^�TV��Z/u��tS6��.�b�����ŚZܨ\e��W�~'M?e�+L�T�T/7jծ��q�M���SF�Q'ۄ�"���
JǨ��\���@w�B�
!����h,:"�Ґ������������)�Th.	A�G�j��~�8��ln,�9�ցn�j�����~]�硯T02���1/6=,��(s�!7�7��@TE\�v��f�Y$pN����cq��t�5��L����(m��7�b����l?��iw�n�2�PT\s�1���I�a;D�]�}՘��<)�IolX�C�GJ(r�L�,�S��kSݎik�o3Yż�uz@�pbi�@������K�1I�[C(���wT���}Ήb���7�!�|�w�H*%)�W>��zs��6P�V#����;X�N��v�7�&˻I.S�A�yr�\�3ظU�,U�y0~hN��ҹ�}Y�/B��n��B��1c� �RK&.��E1�����/�v�}����.=E���f~SU�'��lYY|����$K��*��n��-٨k�_n���/��jm�&���ȅx"�G���	�*hE��h�N�bIN�ֺ$�T���ُ��	qQT\�n5+�B�7��z0���*�"ŕ ��'���8��ҟ�"��o���������(�J��_��p���N�&kN�!ż,� �kZd]�"�?�=[�24�}�Kt����Z��ϙ�Xd_$#8?��\�'_�c����B�g�����r� �Z-�Z�U��=708���D%�8�.�_�L�}-.'���{��R&�=C~N������-ƴ24<�5,��i���c�f^�#I*_f�o�찿L(�erl�vvv��U��SŲ\�,.��ET��Uű�[��O�b������7j�°��)qR[[ۿ�t�}�auTK�1!�Xz��"���2��o���o�����c������U��gbx��tK��j7�db��m�ݶ�P#���TE�F��K��J@_K��B�y��3=19�f��j^ڒ�.2\�(�U�U�X�hѻ����6����˽������` ���s=��    IEND�B`�  K  8   I M G   I M G _ S H A D O W         0         �PNG

   IHDR   �   �   ���k   tEXtSoftware Adobe ImageReadyq�e<  $iTXtXML:com.adobe.xmp     <?xpacket begin="﻿" id="W5M0MpCehiHzreSzNTczkc9d"?> <x:xmpmeta xmlns:x="adobe:ns:meta/" x:xmptk="Adobe XMP Core 5.3-c011 66.145661, 2012/02/06-14:56:27        "> <rdf:RDF xmlns:rdf="http://www.w3.org/1999/02/22-rdf-syntax-ns#"> <rdf:Description rdf:about="" xmlns:xmp="http://ns.adobe.com/xap/1.0/" xmlns:xmpMM="http://ns.adobe.com/xap/1.0/mm/" xmlns:stRef="http://ns.adobe.com/xap/1.0/sType/ResourceRef#" xmp:CreatorTool="Adobe Photoshop CS6 (Macintosh)" xmpMM:InstanceID="xmp.iid:44595DFDEB3F11E1905EF7815B99F340" xmpMM:DocumentID="xmp.did:44595DFEEB3F11E1905EF7815B99F340"> <xmpMM:DerivedFrom stRef:instanceID="xmp.iid:44595DFBEB3F11E1905EF7815B99F340" stRef:documentID="xmp.did:44595DFCEB3F11E1905EF7815B99F340"/> </rdf:Description> </rdf:RDF> </x:xmpmeta> <?xpacket end="r"?>�k  �IDATx����n�P���I��Jv�y�gb��T��&f\憉I$>G]���J�n�[��-~�܃9�\���&����EYa�erm�C��E��Y��O9�F�2���\�-��*g=�W��u]�.�]5Ρ�D똛�m���v�Ő>���A�[HcD��ۘ��킋!}��>�!�i��/�H�T��*�j��,[?��\{N��'�j���nN^k��e��1���Q/$���N��'R�N	��aڊ�X�@H $		�B�B!�� !��@H $@H $		�B�B!B!��@H��@H $ $	�	�B!B!��@H��@H $ $		�B�B!�� !��@H $@H $		�B�B!��l	�B�B!�� !��@H $@H $		�B�B!�� !��@H��@H $ $	�	�B!B!��@H��࿅4�.���>8�y�Op�ˤ���H-"!��Cj1��b�1�ۘ���1�s�����;��}�.�!�>�[̗\����ˏwc(�IL-�M�ދ	��!=Mbj=Րکt��y���*������B�(7F��=��l�e }	f]N�v�3��?h�Ӯ>+���ɴ�x�y�B:�>��缾��J 5��\/<�9�ְ��%Ո��s�`������� �)�e���^    IEND�B`� �   8   I M G   I D _ M E N U _ B K G       0         �PNG

   IHDR   �   8   ���   PLTE���               �����l1   tRNS�f F�脚/   YIDATx^��1�P�MPp����?98��LLǌ��僚�F�k���<.�{d>�z+��e�����������������Sv;�����>�Ch!�0��    IEND�B`�  C  @   I M G   I D _ R I C H _ F I L E _ B K       0         �PNG

   IHDR      2   K^k�   tEXtSoftware Adobe ImageReadyq�e<  �IDATx����+q��޸��Ga����=1y�Hx���)L(ၨeQ+�"Vd��6�2����|}>f�C��<�~��}����[w�{�!�R���7&��B� ����{�5�IA����W+}�a ������f�i\OH��/���WE�Ƣ��/�Z�{2n6P ���w��#/J6J�������uE��Z7�C�|���T���A��4u{��N�F���P-q:���v��{~u�qzq��Mm��5k�vN粊fg_O�4,k�:�gPu�5O�ņp��,��IiEa���!�S�¦2��o
-�U�H�`��f0��`3��f0��a�0������82L-X
�)5��7
V���'�xr�(X�%|h"�>:��W�ܭި�f�P8� ��9U����4MK�桷?x2��Y�!jUɦ�O�������qڥ	�(�I�c�|Hq9�X�E�ϱq�R�A��  -O�x�Nk    IEND�B`� :  D   I M G   I D _ F I L E _ I C O N _ T E X T       0         �PNG

   IHDR   (   (   ~Х^   'PLTE���         ������������O�����V��J�����QD   tRNS�$:m|���   �IDATx^�ͽ�0�у��
Z�l�L M��L�p� �l��{,�{.�D�����t��"�g%밃U�4�E����Y�-�t�R�5�8os�s�6�R��.�����1V�'��޿��������[���0��'��
��7��P��9�a��1D��}��-��84�J}� �w�C�6)��&o(�U=v�
�    IEND�B`�  x   4   I M G   I D _ E M P T Y         0         �PNG

   IHDR   
   
   �2Ͻ   tEXtSoftware Adobe ImageReadyq�e<   IDATx�b���?1���H0��:
 �j��\    IEND�B`�  D   I M G   I M G _ L O G I N _ B O R D E R         0         �PNG

   IHDR   2      nQM�   	pHYs     ��  
MiCCPPhotoshop ICC profile  xڝSwX��>��eVB��l� "#��Y�� a�@Ņ�
V�HUĂ�
H���(�gA��Z�U\8�ܧ�}z�����������y��&��j 9R�<:��OH�ɽ�H� ���g�  �yx~t�?��o  p�.$�����P&W  � �"��R �.T� � �S�d
 �  ly|B" � ��I> ة�� آ� � �(G$@� `U�R,�� ��@".���Y�2G�� v�X�@` ��B,�  8 C� L�0ҿ�_p��H �˕͗K�3���w����!��l�Ba)f	�"���#H�L�  ����8?������f�l��Ţ�k�o">!����� N���_���p��u�k�[ �V h��]3�	�Z
�z��y8�@��P�<
�%b��0�>�3�o��~��@��z� q�@������qanv�R���B1n��#�ǅ��)��4�\,��X��P"M�y�R�D!ɕ��2���	�w ��O�N���l�~��X�v @~�-�� g42y�  ����@+ ͗��  ��\��L�  D��*�A�������aD@$�<B�
��AT�:��������18��\��p`����	A�a!:�b��"���"aH4��� �Q"��r��Bj�]H#�-r9�\@���� 2����G1���Q�u@���Ơs�t4]���k��=�����K�ut }��c��1f��a\��E`�X&�c�X5V�5cX7v��a�$���^��l���GXLXC�%�#��W	��1�'"��O�%z��xb:��XF�&�!!�%^'_�H$ɒ�N
!%�2IIkH�H-�S�>�i�L&�m������ �����O�����:ň�L	�$R��J5e?���2B���Qͩ����:�ZIm�vP/S��4u�%͛Cˤ-��Кigi�h/�t�	݃E�З�k�����w���Hb(k{��/�L�ӗ��T0�2�g��oUX*�*|���:�V�~��TUsU?�y�T�U�^V}�FU�P�	��թU��6��RwR�P�Q_��_���c���F��H�Tc���!�2e�XB�rV�,k�Mb[���Lv�v/{LSCs�f�f�f��q�Ʊ��9ٜJ�!��{--?-��j�f�~�7�zھ�b�r�����up�@�,��:m:�u	�6�Q����u��>�c�y�	������G�m��������7046�l18c�̐c�k�i������h���h��I�'�&�g�5x>f�ob�4�e�k<abi2ۤĤ��)͔k�f�Ѵ�t���,ܬج��9՜k�a�ټ�����E��J�6�ǖږ|��M����V>VyV�V׬I�\�,�m�WlPW��:�˶�����v�m���)�)�Sn�1���
���9�a�%�m����;t;|rtu�vlp���4éĩ��Wgg�s��5�K���v�Sm���n�z˕��ҵ������ܭ�m���=�}��M.��]�=�A���X�q�㝧�����/^v^Y^��O��&��0m���[��{`:>=e���>�>�z�����"�=�#~�~�~���;�������y��N`������k��5��/>B	Yr�o���c3�g,����Z�0�&L�����~o��L�̶��Gl��i��})*2�.�Q�Stqt�,֬�Y�g��񏩌�;�j�rvg�jlRlc웸�����x��E�t$	�����=��s�l�3��T�tc��ܢ����˞w<Y5Y�|8����?� BP/O�nM򄛅OE����Q���J<��V��8�;}C�h�OFu�3	OR+y���#�MVD�ެ��q�-9�����Ri��+�0�(�Of++��y�m������#�s��l�Lѣ�R�PL/�+x[[x�H�HZ�3�f���#�|���P���ظxY��"�E�#�Sw.1]R�dxi��}�h˲��P�XRU�jy��R�ҥ�C+�W4�����n��Z�ca�dU�j��[V*�_�p�����F���WN_�|�ym���J����H��n��Y��J�jA�І����_mJ�t�zj��ʹ���5a5�[̶���6��z�]�V������&�ֿ�w{��;��켵+xWk�E}�n��ݏb���~ݸGwOŞ�{�{�E��jtolܯ���	mR6�H:p囀oڛ�w�pZ*�A��'ߦ|{�P������ߙ���Hy+�:�u�-�m�=���茣�^G���~�1�cu�5�W���(=��䂓�d���N?=ԙ�y�L��k]Q]�gCϞ?t�L�_�����]�p�"�b�%�K�=�=G~p��H�[o�e���W<�t�M�;����j��s���.]�y�����n&��%���v��w
�L�]z�x�����������e�m��`�`��Y�	�����Ӈ��G�G�#F#�����dΓ᧲���~V�y�s������K�X�����Ͽ�y��r﫩�:�#���y=�����}���ǽ�(�@�P���cǧ�O�>�|��/����%ҟ3    cHRM  z%  ��  ��  ��  u0  �`  :�  o�_�F  5IDATx���kA�?;�4iZ�����H��Ċa�����*�G�� �6gO�4x�Ճ`Bw����x�M�)��Mȃa��a�g�{;�}�1�u�-����]� �[�aF@�@qq��qV���j����6	���en90u��(��d.�(�Q�t�}�� �	bR�H�h-D$�{�N����������0T7�P�eY}�ӳx8z�̲�^���?|p_k�Od���Ͻ-�o��D�}͹L���'@E�; |����Rnkw�I+��^o���8��/6���Z�x0x<���[�yo�*��@6�B��|��X���m HW�-�%�������7�^6 ��dR�q�����e�Z"'��4 ��p��S�B�ʪ� W)ŷ���G,Y��d�>��S��ǿV������uk.�����D&w�2���I<=�ǃ�a�n4$�'��M<=���\��Ck��#��"Z��������PH:�q)��*.��(��b��@��A�_#3~5���Y��=R�B-�y���� t��_rv��    IEND�B`��   D   I M G   B T N _ L O G I N _ N O R M A L         0         �PNG

   IHDR   �      �3�V   PLTE	��	��	��   	��	��R�*x   tRNS�& �-*�   KIDATx^��1 !��%�W@�:X'���oS���kG�Y}��h��R�����Z�`��,�7��9P���9^�    IEND�B`� �   @   I M G   B T N _ L O G I N _ H O V E R       0         �PNG

   IHDR   �      �3�V   PLTE<��<��<��   <��<��A$v   tRNS�& �-*�   KIDATx^��1 !��%�W@�:X'���oS���kG�Y}��h��R�����Z�`��,�7��9P���9^�    IEND�B`� �   @   I M G   B T N _ L O G I N _ P R E S S       0         �PNG

   IHDR   �      �3�V   PLTE	��	��	��   	��	���3�"   tRNS�& �-*�   KIDATx^��1 !��%�W@�:X'���oS���kG�Y}��h��R�����Z�`��,�7��9P���9^�    IEND�B`� �   D   I M G   S Y S _ C L O S E _ N O R M A L         0         �PNG

   IHDR         �#§   PLTE               O�   tRNS >M@x�}   4IDAT�c��I��Y�eT40T��R"B�H����,J*��z&��K_  �Nˇ���    IEND�B`�   �   @   I M G   S Y S _ C L O S E _ H O V E R       0         �PNG

   IHDR         �#§   PLTE�aU����ma�������xn~S�1   DIDAT�c��ш���eVPAp�M��T+�( qYE��RF��u54BpYD����u�@_  ���Τ    IEND�B`� �   @   I M G   S Y S _ C L O S E _ P R E S S       0         �PNG

   IHDR         �#§   PLTE�4(����C7�������QG��G8   DIDAT�c��ш���eVPAp�M��T+�( qYE��RF��u54BpYD����u�@_  ���Τ    IEND�B`� |   @   I M G   S Y S _ M A X _ N O R M A L         0         �PNG

   IHDR         c7   	PLTE         �c��   tRNS M;��   IDAT�c���CCC�t ��4L�� �����    IEND�B`�|   <   I M G   S Y S _ M A X _ H O V E R       0         �PNG

   IHDR         c7   	PLTE         �c��   tRNS_O0���   IDAT�c���CCC�t ��4L�� �����    IEND�B`�|   <   I M G   S Y S _ M A X _ P R E S S       0         �PNG

   IHDR         c7   	PLTE         �c��   tRNS+k\*��l   IDAT�c���CCC�t ��4L�� �����    IEND�B`�n   @   I M G   S Y S _ M I N _ N O R M A L         0         �PNG

   IHDR         c7   	PLTE         �c��   tRNS MHǦ<4   IDAT�c8��i ����R��    IEND�B`�  n   <   I M G   S Y S _ M I N _ H O V E R       0         �PNG

   IHDR         c7   	PLTE         �c��   tRNS_[*]+�   IDAT�c8��i ����R��    IEND�B`�  n   <   I M G   S Y S _ M I N _ P R E S S       0         �PNG

   IHDR         c7   	PLTE         �c��   tRNS+kg��+H   IDAT�c8��i ����R��    IEND�B`�  �   H   I M G   S Y S _ R E S T O R E _ N O R M A L         0         �PNG

   IHDR         c7   	PLTE         �c��   tRNS M;��   *IDAT�c�>`
ӌ��ځ*�
f�
��P(�a��Ƒ h�!k�{?    IEND�B`� �   D   I M G   S Y S _ R E S T O R E _ H O V E R       0         �PNG

   IHDR         c7   	PLTE         �c��   tRNS_O0���   *IDAT�c�>`
ӌ��ځ*�
f�
��P(�a��Ƒ h�!k�{?    IEND�B`� �   D   I M G   S Y S _ R E S T O R E _ P R E S S       0         �PNG

   IHDR         c7   	PLTE         �c��   tRNS+k\*��l   *IDAT�c�>`
ӌ��ځ*�
f�
��P(�a��Ƒ h�!k�{?    IEND�B`� �
  8   I M G   T E S T _ I C O N 2         0         �PNG

   IHDR         ;0��   sRGB ���   gAMA  ���a   	pHYs  �  ��o�d  
^IDATHKU��_�W�GQ�"�0�0CGAĂ�f` +ƞĒ������(���ҋ�A�0֬F7���?��}Y���������s�sϽ�{��/�rt���o���/����AFGn���-ޓo�G�ν�����#������G����p7�u1|���#����[]�����>��cp�:7����:*x1v����xx��n�s��!����}�o�"�ò� #���`�!w�po����ro�������|��?_󻌟?���Ox��9��ן�}��}ËW�y��?yȣ�_{�Dó�/����y���,�Woe,x��w��ɋ�<��p����1M����ӏE�_,��ٟ9u�G���ͻ٘��u���������螼����`��s:����=Dec7�����)����_d��-�n����5��'�86�9�9>zfy�9�̜Yf�g��
%`^8���4a���3�O$F�"|������&,v��s0D�c'&i=q��Xr>f���Y�,oC8^�\=�qu��1(��h"��sصc�:��}�8!�.SUPM�OE|��Kr�7�����E"Z�����}�� �������/���96�:�}�.2Voc͆��n�������?RP\A}C������PY^���&n��2t�=����q��mu������S"������-^�iQ6Qvb�����<N_j��2v�?��o���l'�\!_\�7u���C]c+%���q1�$%E?��QC_W=����*9OkC�M%�2z:j��B_O#��pA��CW`
OaYR.��۱dn!ٶ��u;�/j���X����{�y�K��o������2����Z�-��V��X�3��%t��y�՗h������\F�xq2�	D.Lb�r+ɖUX�V�"9��8+KbS����E�����g�RXFQy5��U>r�={ws��a�*K��n������
��*h�-������5t����^�������*�Jk�(�����Ғ.����s8p���u�?t�ʚf���~�6=��5wp��L�k8q�{v���ܹ���:ڮ��X[GKC�����Jن2t��ܸ~����t�����Eg{]��Dy?�=�tt�	��]����ݙ��T�e�_\�Վ~�z��i�����ʫ��RPP%�53JU k4A�6!ik������FAS������>���J�:���UH*�)�h����⚫�
IY]�Ts�����^j��	��m�NCs?M��T�v
:���rPY!�ߞ.����=�������^Vo�\�q)k��� 6e5�ˬ̏I%j���ELq�D&�(�NJ�6�m�I�!:.�D���o�d������.s�����:J˪�}ුY��L����3���L�]��9��^�Xs����/Dn-���Bh��d��K@�H�2;��md}�%�7~���5[w���/s����9�D�b��eߥ�b7>D�d�񎐣&��!*��,Bbr������_�������7G���BS�4%���I.��%����a��}|��q�ș.�%��٘��{h�B�L����G���L|"����_�X`�?̆�i^�9	�0+��2��|��R��""�p����\s��-�?x9:7SS&�q	H�!��T��1+؆o�J�B�	Z����G�}���/����t����g����e���`nH�8�hO?y�	K��@��?!"n:'�$�5R�F�lL��?�=�S*�df�K�W���%i;��p�}�UQ�8KmX��c�)��8iw�E� �Y!���������rW+�S�T��w2�{��R�I��Sq�O��g��K���o,����,�l��n���G�I�A��U��Ɯ�4<L�̑N̎H�038���q���&�MV�K���Q��dL�0E;$�����laZ��QN~��<cpJ%4q+�3w�������Pai̐�͔��	��Sm�bN�ќ�$i�;(��XqJ�����9� ��t�J�&�J`���,�U(���fϷ���	���~�	�tD���Y~�V("'I���`A��y��L�9�	��|���6���)"��'N��t9-S�+�{I�Zp��{H�Uh%\)��ĵ�y��T�E�������L��10�A
�R��C`��� HԺ���$���P�ܨM�-r���"kL��f���8�h�l%D�l�$���DC�Ƀ���d�0Q�2Aξ��)r��eB�q��X=%��Vh[���s5Z���TQhPsJ�T����,�����I�[c���`��m\���Ig&�Љ"�Q�d=G�x5?Zٺw��R�&?�&��&�-����0% S����qb�\����'!���)��UL(8�[�wB&PO�^�tYl�LB5�!�ũ�)k�\���_�6!W����ġ"W�'�+Bq�+n~���S�~�\��;�R�!�{���Y�5Rq�"�&�4¿�`�v+b��!q��?ɉ~|N	�?buy�������*t�q��B�dP{g��P�A�M�*�V���6+Bg�Wɀ�j��	�Ǫ�\̲�B��5�3�I�ظ�MڧH�+BE0N:����"FH�C����I��Vi�Vu�ߑ��^��2?!    IEND�B`�   =  8   I M G   C H A T _ N O R M A L       0         �PNG

   IHDR   (   (   � H_   ZPLTE   ������������������������������������������������������������H�   tRNS ����gC�mV�.��L5۰u^<%|�����  uIDAT8˭�ۖ�0EiK�ܯ���s蠵��\�f�T�iN�I�7��1WB��~,�>i�|�]�"�7}`1S{O�,�L�߬�FWE6�z!y����:{�q%9��^$�@���P���̺.��T@�zʀ88��,=^!��)<��D28�r~W�'4�۳!τ!.�*8�,��=NɖT)t����P���s��~om?����(8��Y]o�s��m0�[��`��@��X�S���?,"���s֯Zi�P=�V�.a4;�"�m�T��,�o?}�����8�X�^�@|�/����z/K\���N6�/\KhV������z�եT�1z���k�q��[�(w�#��C��w�4��LW���d�����Bq(�͐e<    IEND�B`�   U  8   I M G   C H A T _ H O V E R         0         �PNG

   IHDR   (   (   � H_   `PLTE   ^cy^cy^cy^cy^cy^cy^cy^cy^cy^cy^cy^cy^cy^cy^cy^cy^cy^cy^cy^cy^cy^cy^cy^cy^cy^cy^cy^cy^cy^cy^cy/i Q   tRNS ���g����VC��L�n5.�u^<|"�'6�~.  �IDAT8˭TY�� �MD�.1�}�[N�(&o���)z)�$+��� T�n��HY�YGye!踧2a��s�0B��xn��׷��\w���G14����~�"��M���#s~��O�����,�?.1�����i$�� ��9�$����
�A�K��	rF��R��<9EeK
�����p*}N����.���[%�D����_���\?�pAt>&�4�V��S��.U�m28�S����$N�c�B�;�0���2����+4�T��*_�����J/Z����l\V���\����%�lM��U��<j�[�a(dpR�h#}哛 *<l�L"D�Rb���'U���
�(���A
!�D�2D+��@,�W�SyA��FbΤ�pM�??�+A�@r    IEND�B`�   D  8   I M G   C H A T _ P R E S S         0         �PNG

   IHDR   (   (   � H_   �PLTE    �� �� �� �� �� �� �� �� �� �� �� �� �� �� �� �� �� �� �� �� �� �� �� �� �� �� �� �� �� �� �� �� �� �� �� �� �� �� ���������������������������u��W��=��2�����b�   'tRNS �����Ҥ�͸�lhT@5*�t_D"�Ũ��xWL<�1U�u�  *IDAT8˭��r� �aרQ��Y���A�o��j��� e:�/���� ��E�$�g�p�f+� .'|���1+?/��i"����(��f�Ӓ3�l��B�L����z�kh�� ��3�ԁC�2����DZ:�Ѕ������qu?ϐ����������HOPw�G~^4�T[z��n��V�x�~� ׵�u�U\Y��������;?3���ۆ�֨)�:���w9���R�31���Èo�ri��Þb�5j7��\��3��Lr7Ǐg�2�������I�d����&_�_�~c�    IEND�B`��  @   I M G   C O N T A C T S _ N O R M A L       0         �PNG

   IHDR   (   (   � H_   QPLTE   �����������������������������������������������������Κ�   tRNS �G����W-ȫ�>��O~wc"mӑ���n  6IDAT8˵�ۚ� ��BO��������RXo��f 	��Q7��ZtM]�+ġ�[4�B?v�R�ɂ�����[� Nf�gpj;%�������d�rWjPIb��"@�~3���&I<�)�谯H+y����϶�c�o���`��m�j�r��B��\�+�l&�i�+Nt����Pb�7 ��w��%��E���',kS��j�pפ ����: �(W�G@�^� ������>�9���-���sIc{̻00d䕆-��!�m�t4�TA]�#	sU���7�_r��N��*�����"��7j    IEND�B`�    @   I M G   C O N T A C T S _ H O V E R         0         �PNG

   IHDR   (   (   � H_   ZPLTE   ^cy^cy^cy^cy^cy^cy^cy^cy^cy^cy^cy^cy^cy^cy^cy^cy^cy^cy^cy^cy^cy^cy^cy^cy^cy^cy^cy^cy^cy�w��   tRNS ���TF-ȢM>�ຫv�~c���m[%O	��  ;IDAT8˵�ۖ� EA�]��w��o�Vp�q��ɬl�pX!����2�h�<�����w"�m��N��Ť ��v�Ҿ�m	J�����WG,ᶚ�*tt�`7�ƗX5h6��8�.��>Z�q�C�	>��c�-�g��+8���|խ^ll���Q�3�Ls�*5�'�R?��Me͜O��dGy ����jv�"S�� ���鹉/�ޓ���P�>F�3�Y�~_Z^�욫N}��Y��V�:���LkNmnqc�c���`�N�K�u��?sd����ދ��{�JOB8AvcG��N�y���3��}�I��W�'6X�ҭ    IEND�B`� �  @   I M G   C O N T A C T S _ P R E S S         0         �PNG

   IHDR   (   (   � H_   WPLTE    �� �� �� �� �� �� �� �� �� �� �� �� �� �� �� �� �� �� �� �� �� �� �� �� �� �� �� �ۖL��   tRNS =��H*��maX������|xPC�3ʓ0��   �IDAT8˵�I�0@Q��fbK�����28a�_?,��xG�;�N7Gޱ��[�Y�.K�z�3��a�	h0���>�*�����p#v�j�p%a�ӯ��HHV�N@�o'�2 }7 �T|�|u3d��i���Y�n�aeoiS�W��]��&L�S������4�n!n�|��+A�Oh��u�+�xBA�&�F���'du�1x���Qhܞ��    IEND�B`�   Q  8   I M G   A P P _ N O R M A L         0         �PNG

   IHDR   (   (   � H_   ZPLTE   ������������������������������������������������������������H�   tRNS �0î�Y�@'�G �wR��Ѓ`��j89�C  �IDAT8��SYv� D��[�s�kc��Ͽ��)�����Ü�><P��B*��)M�/E �_)����ug1/#X+i��"^m,�#�c� 4�6'��]�P�e��N\�Wh�|q%�����p�Ɂ�Fl ���<q�+ ���d1��g\�ˊ�?r�mV�F7��E@��8&^oGJ���"DP�����Jh
D�]˖Q:��ʪs�Vi?]����I�VI^Q���>��L�n1���o��B� s6[-���:���"���N,�Pk��O�k��/�pm	����^?^�Q����M�������(*�U�#[� 0nnX�6�2	��T�I�60�c�F�$�x��g�@F�&<��U=�Xq(�4�J�=~ OL1�V���    IEND�B`�   Y  4   I M G   A P P _ H O V E R       0         �PNG

   IHDR   (   (   � H_   ZPLTE   ^cy^cy^cy^cy^cy^cy^cy^cy^cy^cy^cy^cy^cy^cy^cy^cy^cy^cy^cy^cy^cy^cy^cy^cy^cy^cy^cy^cy^cy�w��   tRNS ���)�YD3!�����vSK=��a�~j	��  �IDAT8��Tٖ� eQ\�֥N���o�P��י<�	�\�*����֤��^`�҈R�9�A�SI\�5E���U��[a�NA)R\/D�L�!}|�SBY' ;狣8����r����DϘ:��Y�Gw.�k��"r������ע|�E .'`KT���
!��ס���@<�\�����Kʍ����Jne��hpXFC3��8�D�a6�ʈ!��e��Er���M�'�FWR n�:?��|��B^�`Fٚ�ԎrS���pc�ݙ�b� ��Q��M�'x�U���a��r�"�1�uD�ʹ��ђ�[�e�!�A�@c�iC��w5Z�b��S���~8>c����m0�R��{�_s)㦻5UM�U�R��oDYE�dk��xĠ$]K���k�gՊ��_��0"�q3    IEND�B`�      4   I M G   A P P _ P R E S S       0         �PNG

   IHDR   (   (   � H_   lPLTE    �� �� �� �� �� �� �� �� �� �� �� �� �� �� �� �� �� �� �� �� �� �� �� �� �� �� �� �� �� �� �� �� �� �� �۩�Q�   #tRNS �8J2�X"���uC��*𿰒�me]Q�Âz��.���  @IDAT8�ْ͓� E/5�c�Y���qJ�$v(�8s^@84v�⿑5�ű�(u z/h� z�-�דk� ��#���.�	��H3y�3Kz���gOn@���%'�81�'��G&V\l����{��:3����ETLL���Kߒ9�as�[O�fEjp��xB��	>9�{�֥��'��^�L_Z�ms�wS�A����;�Vq��W 9�'ɉ��N�^嶍ՓV�ek�����Z��ɏ
�X3�ux��]ϙ�/���T6=�s�&[��`!D���0�3U�ʉEif��
���f@P���Qp�!Sf�{~�h޾��w    IEND�B`��  <   I M G   S E T U P _ N O R M A L         0         �PNG

   IHDR           szz�   tEXtSoftware Adobe ImageReadyq�e<  &iTXtXML:com.adobe.xmp     <?xpacket begin="﻿" id="W5M0MpCehiHzreSzNTczkc9d"?> <x:xmpmeta xmlns:x="adobe:ns:meta/" x:xmptk="Adobe XMP Core 5.6-c067 79.157747, 2015/03/30-23:40:42        "> <rdf:RDF xmlns:rdf="http://www.w3.org/1999/02/22-rdf-syntax-ns#"> <rdf:Description rdf:about="" xmlns:xmp="http://ns.adobe.com/xap/1.0/" xmlns:xmpMM="http://ns.adobe.com/xap/1.0/mm/" xmlns:stRef="http://ns.adobe.com/xap/1.0/sType/ResourceRef#" xmp:CreatorTool="Adobe Photoshop CC 2015 (Windows)" xmpMM:InstanceID="xmp.iid:99632AD08F8611E6AC85B777DD2FCE40" xmpMM:DocumentID="xmp.did:99632AD18F8611E6AC85B777DD2FCE40"> <xmpMM:DerivedFrom stRef:instanceID="xmp.iid:99632ACE8F8611E6AC85B777DD2FCE40" stRef:documentID="xmp.did:99632ACF8F8611E6AC85B777DD2FCE40"/> </rdf:Description> </rdf:RDF> </x:xmpmeta> <?xpacket end="r"?>�7�6   HIDATx�b�o��0��J� ���:`� K���Q0�Q��r`�2u�he4�F0�G�Q�ܺ  � �!�=�ܰ    IEND�B`��  8   I M G   S E T U P _ H O V E R       0         �PNG

   IHDR           szz�   tEXtSoftware Adobe ImageReadyq�e<  &iTXtXML:com.adobe.xmp     <?xpacket begin="﻿" id="W5M0MpCehiHzreSzNTczkc9d"?> <x:xmpmeta xmlns:x="adobe:ns:meta/" x:xmptk="Adobe XMP Core 5.6-c067 79.157747, 2015/03/30-23:40:42        "> <rdf:RDF xmlns:rdf="http://www.w3.org/1999/02/22-rdf-syntax-ns#"> <rdf:Description rdf:about="" xmlns:xmp="http://ns.adobe.com/xap/1.0/" xmlns:xmpMM="http://ns.adobe.com/xap/1.0/mm/" xmlns:stRef="http://ns.adobe.com/xap/1.0/sType/ResourceRef#" xmp:CreatorTool="Adobe Photoshop CC 2015 (Windows)" xmpMM:InstanceID="xmp.iid:9F691D908F8611E698B7B3163A58ED78" xmpMM:DocumentID="xmp.did:9F691D918F8611E698B7B3163A58ED78"> <xmpMM:DerivedFrom stRef:instanceID="xmp.iid:9F691D8E8F8611E698B7B3163A58ED78" stRef:documentID="xmp.did:9F691D8F8F8611E698B7B3163A58ED78"/> </rdf:Description> </rdf:RDF> </x:xmpmeta> <?xpacket end="r"?>,6�#   HIDATx�b�K�dH������LF0��%B��(u��F|90Z�:`�2M�͆�u��Fn] ` ��g�آ    IEND�B`��   8   I M G   F A C E _ N O R M A L       0         �PNG

   IHDR         � >   'PLTE   �������������������������^��   tRNS �0��ܚ�RD�u�?�"   qIDAT�c�	ԓŊ ,wA �XMU��%�Lv1�� S�$�,$&/�b2@L&1 ���YHB��`�x����X�7��)��:(![���$G� ��7�߽    IEND�B`�  �   8   I M G   F A C E _ H O V E R         0         �PNG

   IHDR         � >   -PLTE   ^cy^cy^cy^cy^cy^cy^cy^cy^cy^cy^cy^cy^cy^cy2R)V   tRNS ����4,���RD�u��   qIDAT�c�	J'I�CX��@b1/TI6s�2 2Y%
���Du�\��pt�t�[�EȜ� b�I��`�B@B�+`z���&	��"{��-Q��IŠH�
��� �  $���H�    IEND�B`�    8   I M G   F A C E _ P R E S S         0         �PNG

   IHDR         � >   0PLTE   ������������������������������1B��   tRNS ���4,����RD�ug�c�   rIDAT�c�	R&�p��D��#�Ÿ�(PT�� ���#�����Ȍ7�%�
�p�0}2����?�L{���@�?�����_PH���
`m�f��E`�V ,F8�H\  ��+��c1    IEND�B`�  r  @   I M G   S E N D P I C _ N O R M A L         0         �PNG

   IHDR         ��   	pHYs     ��  
MiCCPPhotoshop ICC profile  xڝSwX��>��eVB��l� "#��Y�� a�@Ņ�
V�HUĂ�
H���(�gA��Z�U\8�ܧ�}z�����������y��&��j 9R�<:��OH�ɽ�H� ���g�  �yx~t�?��o  p�.$�����P&W  � �"��R �.T� � �S�d
 �  ly|B" � ��I> ة�� آ� � �(G$@� `U�R,�� ��@".���Y�2G�� v�X�@` ��B,�  8 C� L�0ҿ�_p��H �˕͗K�3���w����!��l�Ba)f	�"���#H�L�  ����8?������f�l��Ţ�k�o">!����� N���_���p��u�k�[ �V h��]3�	�Z
�z��y8�@��P�<
�%b��0�>�3�o��~��@��z� q�@������qanv�R���B1n��#�ǅ��)��4�\,��X��P"M�y�R�D!ɕ��2���	�w ��O�N���l�~��X�v @~�-�� g42y�  ����@+ ͗��  ��\��L�  D��*�A�������aD@$�<B�
��AT�:��������18��\��p`����	A�a!:�b��"���"aH4��� �Q"��r��Bj�]H#�-r9�\@���� 2����G1���Q�u@���Ơs�t4]���k��=�����K�ut }��c��1f��a\��E`�X&�c�X5V�5cX7v��a�$���^��l���GXLXC�%�#��W	��1�'"��O�%z��xb:��XF�&�!!�%^'_�H$ɒ�N
!%�2IIkH�H-�S�>�i�L&�m������ �����O�����:ň�L	�$R��J5e?���2B���Qͩ����:�ZIm�vP/S��4u�%͛Cˤ-��Кigi�h/�t�	݃E�З�k�����w���Hb(k{��/�L�ӗ��T0�2�g��oUX*�*|���:�V�~��TUsU?�y�T�U�^V}�FU�P�	��թU��6��RwR�P�Q_��_���c���F��H�Tc���!�2e�XB�rV�,k�Mb[���Lv�v/{LSCs�f�f�f��q�Ʊ��9ٜJ�!��{--?-��j�f�~�7�zھ�b�r�����up�@�,��:m:�u	�6�Q����u��>�c�y�	������G�m��������7046�l18c�̐c�k�i������h���h��I�'�&�g�5x>f�ob�4�e�k<abi2ۤĤ��)͔k�f�Ѵ�t���,ܬج��9՜k�a�ټ�����E��J�6�ǖږ|��M����V>VyV�V׬I�\�,�m�WlPW��:�˶�����v�m���)�)�Sn�1���
���9�a�%�m����;t;|rtu�vlp���4éĩ��Wgg�s��5�K���v�Sm���n�z˕��ҵ������ܭ�m���=�}��M.��]�=�A���X�q�㝧�����/^v^Y^��O��&��0m���[��{`:>=e���>�>�z�����"�=�#~�~�~���;�������y��N`������k��5��/>B	Yr�o���c3�g,����Z�0�&L�����~o��L�̶��Gl��i��})*2�.�Q�Stqt�,֬�Y�g��񏩌�;�j�rvg�jlRlc웸�����x��E�t$	�����=��s�l�3��T�tc��ܢ����˞w<Y5Y�|8����?� BP/O�nM򄛅OE����Q���J<��V��8�;}C�h�OFu�3	OR+y���#�MVD�ެ��q�-9�����Ri��+�0�(�Of++��y�m������#�s��l�Lѣ�R�PL/�+x[[x�H�HZ�3�f���#�|���P���ظxY��"�E�#�Sw.1]R�dxi��}�h˲��P�XRU�jy��R�ҥ�C+�W4�����n��Z�ca�dU�j��[V*�_�p�����F���WN_�|�ym���J����H��n��Y��J�jA�І����_mJ�t�zj��ʹ���5a5�[̶���6��z�]�V������&�ֿ�w{��;��켵+xWk�E}�n��ݏb���~ݸGwOŞ�{�{�E��jtolܯ���	mR6�H:p囀oڛ�w�pZ*�A��'ߦ|{�P������ߙ���Hy+�:�u�-�m�=���茣�^G���~�1�cu�5�W���(=��䂓�d���N?=ԙ�y�L��k]Q]�gCϞ?t�L�_�����]�p�"�b�%�K�=�=G~p��H�[o�e���W<�t�M�;����j��s���.]�y�����n&��%���v��w
�L�]z�x�����������e�m��`�`��Y�	�����Ӈ��G�G�#F#�����dΓ᧲���~V�y�s������K�X�����Ͽ�y��r﫩�:�#���y=�����}���ǽ�(�@�P���cǧ�O�>�|��/����%ҟ3    cHRM  z%  ��  ��  ��  u0  �`  :�  o�_�F   �IDATx�b���?51��0��y����ɗ�'�'_�o����w���
<S�<��D|��+]��o�|��y���ɶ�0�)l:��a������'gS�@�����!�R'`Iw�P��؆'1��7O�e"��
j�LJ���2uK�A]� ���!��    IEND�B`�  �   <   I M G   S E N D P I C _ H O V E R       0         �PNG

   IHDR         � >   'PLTE   ^cy^cy^cy^cy^cy^cy^cy^cy^cy^cy^cy^cy�*R�   tRNS �ą(�7/�]@
^g   GIDAT�c�t�@��(8 dB$yЙ�p�,�@���L<� e�˜��2�6�3Ydඹ�-F��2B  �:;:��M    IEND�B`� �   <   I M G   S E N D P I C _ P R E S S       0         �PNG

   IHDR         � >   -PLTE   �������������������������������v   tRNS �ą(���7/�]@��B�   HIDAT�c���A��;(x dB$�Й�pf� Q ͱ�l|� erʽ��2��{�t�ɒ��n1�� ]�DuBS^\    IEND�B`�  8   I M G   C U T _ N O R M A L         0         �PNG

   IHDR         �W�?   <PLTE   ��������������������������������������`$   tRNS ��Vy�Ͼ[h�䤉B-���}\�   yIDATӥ�Y� �@�����-[���ʓ�GÓ�܏�2Pb�IC&b�3�6Z	�?f�27�C�����K&�ʹ��*�<���O��B~�뎚��l��ų�,l�`���6���t�ם�?y�e�lr    IEND�B`�  7  4   I M G   C U T _ H O V E R       0         �PNG

   IHDR         �W�?   HPLTE   ^cy^cy^cy^cy^cy^cy^cy^cy^cy^cy^cy^cy^cy^cy^cy^cy^cy^cy^cy^cy^cy^cy^cy���L   tRNS ��Wz��S�Ǌp��8,"�~e���   �IDATӕ��� DI­�T�e��OK���fr�Y6k.ǽ�c?Z@�(�X��=A<>%�oCvu�A6c6�������;���1V��9�^��%�����~�V���-���g��.�0DA����v�^�
W��"� 9�     IEND�B`� <  4   I M G   C U T _ P R E S S       0         �PNG

   IHDR         �W�?   NPLTE   �����������������������������������������������������]   tRNS �	V�z�㨊p�Ľ�1'̝eP=�!x�   �IDATӕ�Y�0D�q�f�6��h-�&yB�i��ĞWR�Y���<0�*#w{�wRֈB��b�o����4��if:pǭ��z�i��c�%�Tq���s�=e	H"�	��CH�M�M���ľ;�+|���C��     IEND�B`��   @   P N G   I D _ S E N D B T N _ L E F T       0         �PNG

   IHDR   4      G8Õ   PLTE���������   ���a�9�   tRNS�& �7ZO   3IDATx^��1 @��+��@ο&��c���F�)����ɫ�(F$�֘��H�:k    IEND�B`� �   D   P N G   I D _ S E N D B T N _ R I G H T         0         �PNG

   IHDR          i}�   PLTE���������   ������G�4�   tRNS�& (F�V�   0IDATx^�ѱ 0BQ�s�W��c� �B*@�-���� E�}�6k�    IEND�B`��   D   P N G   I D _ C H A T B T N _ C L O S E         0         �PNG

   IHDR   F      G��   tEXtSoftware Adobe ImageReadyq�e<   �IDATx���A�0DѬF8APeA�p�@T�8��/�s���������6(��QǪ����g�����>VQ���E�yjx���a�lK�5Sph  `�`�`0� s��&�a^84I<��l�:�*�0�[��*W�(��` �l'��k0    IEND�B`��   L   P N G   I D _ S E N D B T N _ S P L I T L I N E         0         �PNG

   IHDR         �Ds�   PLTE   ���������������������#~�_   tRNS A4*<9sN�f   .IDATx^M�K 0�H��J��J@���^`�w�D;���4v����L14B^    IEND�B`� 3  D   P N G   I D _ S E N D B T N _ A R R O W         0         �PNG

   IHDR   N      T}��   tEXtSoftware Adobe ImageReadyq�e<   �IDATx����0�1S�Jw`X�m��b�1��BN�R���d�R����9��y���p p?�}��9dM��볊U블��^b-Sɋ��t�gu�
��]){�����O+���X J��Y
n�&M
��zc.��e�&�ia�����lҬ@�Lc	.��e�67��
O���p��a�� p p����� s�'Y�W5?    IEND�B`� :  D   P N G   I D _ F I L E _ I C O N _ T E X T       0         �PNG

   IHDR   (   (   ~Х^   'PLTE���         ������������O�����V��J�����QD   tRNS�$:m|���   �IDATx^�ͽ�0�у��
Z�l�L M��L�p� �l��{,�{.�D�����t��"�g%밃U�4�E����Y�-�t�R�5�8os�s�6�R��.�����1V�'��޿��������[���0��'��
��7��P��9�a��1D��}��-��84�J}� �w�C�6)��&o(�U=v�
�    IEND�B`�  �   <   P N G   I D _ F E T C H _ M O R E       0         �PNG

   IHDR         �[A�   !PLTEN��N��N��N��N��N��N��N��N��������	#r   tRNS���nmo�f+�   RIDATx^5ˡ�  ���;=+�N1���`t�+(������B0�����Yj�'5D0Z+�|%h$f�Bz
��@�� �w��n� v��94|u    IEND�B`�C  @   P N G   I D _ R I C H _ F I L E _ B K       0         �PNG

   IHDR      2   K^k�   tEXtSoftware Adobe ImageReadyq�e<  �IDATx����+q��޸��Ga����=1y�Hx���)L(ၨeQ+�"Vd��6�2����|}>f�C��<�~��}����[w�{�!�R���7&��B� ����{�5�IA����W+}�a ������f�i\OH��/���WE�Ƣ��/�Z�{2n6P ���w��#/J6J�������uE��Z7�C�|���T���A��4u{��N�F���P-q:���v��{~u�qzq��Mm��5k�vN粊fg_O�4,k�:�gPu�5O�ņp��,��IiEa���!�S�¦2��o
-�U�H�`��f0��`3��f0��a�0������82L-X
�)5��7
V���'�xr�(X�%|h"�>:��W�ܭި�f�P8� ��9U����4MK�桷?x2��Y�!jUɦ�O�������qڥ	�(�I�c�|Hq9�X�E�ϱq�R�A��  -O�x�Nk    IEND�B`�   @   P N G   I D _ R I C H _ W A R N I N G       0         �PNG

   IHDR         (-S   ?PLTE   �B9�80�?7�@7�B9         �A9�2+c�:2   �?6�>6�XP�SK�MD����F@fD��   tRNS �����l0�"WXޡ�o   }IDATx^]�Q� QQ@�l�֕u�6�����Ą9c��g�a�6d[������=��qx_��WБ ������d�59�5��?�vn�gP�&* �z}��_i�`o�S�L
�_i����
q=�J    IEND�B`�   �  H   P N G   I D _ R I C H _ L E F T _ B U B B L E       0         �PNG

   IHDR   (   (   ���m   tEXtSoftware Adobe ImageReadyq�e<  pIDATx��;/DA���Y�SJh4	�T[�D�+Qi=�R�� 
�*4!��f-"�E��,6�o�S�.3s�N1'�r�{�y�s�L�a��hJ8^�4�������]�3�	�p/jP�+؀���8�y��%�V�	j�^��l������T�og�R���0���nT�\Y�V,����
N���h�Z��<۠C2��]#��\a2�<�`R���������@�NE	� -���꿸�0 G.7w0.��r7s����^�zA/h$h�q��
�,�TO-��
Z�h�aOU�,u��:Y�5�#��aI��L���,�!37o&��K�u�U���g(�&ʁ������{�
�����Q{�ǧ  �O==!�    IEND�B`�    L   P N G   I D _ R I C H _ R I G H T _ B U B B L E         0         �PNG

   IHDR   (   (   ���m   tEXtSoftware Adobe ImageReadyq�e<  &iTXtXML:com.adobe.xmp     <?xpacket begin="﻿" id="W5M0MpCehiHzreSzNTczkc9d"?> <x:xmpmeta xmlns:x="adobe:ns:meta/" x:xmptk="Adobe XMP Core 5.6-c067 79.157747, 2015/03/30-23:40:42        "> <rdf:RDF xmlns:rdf="http://www.w3.org/1999/02/22-rdf-syntax-ns#"> <rdf:Description rdf:about="" xmlns:xmp="http://ns.adobe.com/xap/1.0/" xmlns:xmpMM="http://ns.adobe.com/xap/1.0/mm/" xmlns:stRef="http://ns.adobe.com/xap/1.0/sType/ResourceRef#" xmp:CreatorTool="Adobe Photoshop CC 2015 (Windows)" xmpMM:InstanceID="xmp.iid:CE4D9518248111E5880FD78BF11FF7DB" xmpMM:DocumentID="xmp.did:CE4D9519248111E5880FD78BF11FF7DB"> <xmpMM:DerivedFrom stRef:instanceID="xmp.iid:CE4D9516248111E5880FD78BF11FF7DB" stRef:documentID="xmp.did:CE4D9517248111E5880FD78BF11FF7DB"/> </rdf:Description> </rdf:RDF> </x:xmpmeta> <?xpacket end="r"?>�bf  }IDATx�b���?�`L��:p�;��E��~j� �bE f'î�@|���, ~l7�o#�\t���L*�6ȱ- �����:n+�� �8�����~9� "��(j�R�����=+��=)!�B'ǁ� G��ׁ�K�@��� �Uh�o��H�pr�R\Q<Ў�g@<0�$?�E�0���2ǭ�2���T�ѩ��:l�`m,<����֨G8��Qa��I�Gg>&Ձ;�����:p.��cKf)I�,� ��tr`-��\\�{h�9@�M%��j�do ���}Tq!��Č�B;�!
 VbV2��}���ch@P��њdԁ#ف  �k��,t\    IEND�B`�   �   D   P N G   I D _ R I C H _ S Y S M S G _ B K       0         �PNG

   IHDR         � >   PLTEinp   inpinpinpт��   tRNS2 )G�ʭ   GIDATx^����@'bK�\�`�(����k^��$ؒ��	�dc���ғ�� K����9��3�#gz?�u� Z]�    IEND�B`�  @   P N G   I D _ D E F _ V S C R O L L         0         �PNG

   IHDR          /�9�   tEXtSoftware Adobe ImageReadyq�e<  &iTXtXML:com.adobe.xmp     <?xpacket begin="﻿" id="W5M0MpCehiHzreSzNTczkc9d"?> <x:xmpmeta xmlns:x="adobe:ns:meta/" x:xmptk="Adobe XMP Core 5.6-c067 79.157747, 2015/03/30-23:40:42        "> <rdf:RDF xmlns:rdf="http://www.w3.org/1999/02/22-rdf-syntax-ns#"> <rdf:Description rdf:about="" xmlns:xmp="http://ns.adobe.com/xap/1.0/" xmlns:xmpMM="http://ns.adobe.com/xap/1.0/mm/" xmlns:stRef="http://ns.adobe.com/xap/1.0/sType/ResourceRef#" xmp:CreatorTool="Adobe Photoshop CC 2015 (Windows)" xmpMM:InstanceID="xmp.iid:E050EAF21AA111E7A3EAD603AF6FA6A7" xmpMM:DocumentID="xmp.did:E050EAF31AA111E7A3EAD603AF6FA6A7"> <xmpMM:DerivedFrom stRef:instanceID="xmp.iid:E050EAF01AA111E7A3EAD603AF6FA6A7" stRef:documentID="xmp.did:E050EAF11AA111E7A3EAD603AF6FA6A7"/> </rdf:Description> </rdf:RDF> </x:xmpmeta> <?xpacket end="r"?>L��4   ~IDATx��;
�0D7+~����?����Eu�E��^x�l&C�Z�$۾5��#W(u����b�.�L)�D;)Lz�a�9�y+�J��E�ά~�-�@�&�@��F2"�.~�"� ����'"    IEND�B`�  (B      �� ��             (   @   �                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                  EGGEGGEGGEGGEGGEGGEGGEGGEGGEGGEGGEGGEGG	EGGEGG                                                                                                                                                                                            EGGEGG
EGGEGG"EGG1EGG@EGGMEGGVEGG[EGG\EGG[EGGVEGGNEGGCEGG4EGG%EGGEGGEGGEGG                                                                                                                                                                    EGGEGGEGGEGG"EGG7EGGOZJTryId��Gp��@zն*t��:���0�Zm�{K�qLחpX�aN�eXM|EGGUEGG=EGG(EGGEGG
EGG                                                                                                                                                    EGGEGG	EGGEGG-EGGJEGGjsD^��@t��:������������������������mH���.���8��=�ЁJ�sJہdR�MKIwEGGTEGG6EGGEGGEGG                                                                                                                                    EGGEGGEGGEGG.EGGRWHQ��Eo��.������ ��� ��� ��� ��� ��� ��� ��� ��� ���'w���0���0���/���-���/���4�߀?�rI�mZM�EGG_EGG9EGGEGG
EGG                                                                                                                        EGGEGGEGG%EGGJTIP��Ix��"��� ��� ��� ��������������������������� ������pE���.���2���2���2���1���/���.��8��V�p^O�EGGYEGG/EGGEGGEGG            :AA:AA:AA:AA:AA:AA:AA:AA:AA:AA:AA:AA                                            EGGEGGEGGEGG5EGGg�Oq��$��� ��� ��� ������������������������������������ ���N]���,���2���2���2���2���2���1���0���+��8��uP�RNJ~EGGCEGGEGG
EGG:AA:AA:AA:AA:AA:AA:AA:AA:AA:AA:AA:AA:AA:AA:AA:AA                                EGGEGGEGGEGGC\LV��G������ ��� ������������������������������������������ ���4n���-���2���2���2���2���2���2���2���2���0���-�ۀB�zfX�EGGVEGG'DGG>CC:AA:AA	:AA:AA:AA:AA:AA:AA:AA:AA:AA:AA:AA	:AA:AA                            EGGEGGEGGEGGMtLa��"��� ��� ������������������������������������������������ ���&y���2���1���2���2���2���2���2���2���2���2���2���-��9��qX�EGGdEGG.AEE<BB:AA:AA�4qr�7gH:AA:AA:AA:AA�9a5�3t��9a4:AA:AA:AA                            EGGEGGEGGP|Ll����� ��� �� ������������������������������������������������ ���~���5���1���2���2���2���2���2���2���2���2���2���2���/���.��zW�EGGeCFF.>CC:AA�5ox����(�8cP:AA':AA':AA(�4r�����4s�:AA :AA:AA                        EGGEGGEGGLWPz�i7��]'��x'��������� ��������������������������������������������� �����~5���0���2���2���2���2���2���2���2���2���2���2���2���0���-��{Y�DFFO?DD)�5ox�5o��4y��3y��5o��8ef�;YL�5o��3v��6x��3v��4q�}<T':AA                    EGGEGGEGGDYUr�S1��I&��M,��H,��F.��t(������ �� ��������������������������������������� �����~6���0���2���2���2���2���2���2���2���2���2���2���2���2���,��B�ROMl�8h��j]��sX�ŘD�ЅN��sX��Wg��Ep��sX��sX�;��sX��sX��4r�:AA                EGGEGGEGG7SS`�[=��M&��Q+��Q+��Q+��Q+��G-��Q.��������� ������������������������������������ ���~���5���1���2���2���2���2���2���2���2���2���2���2���2���2���.�݃E�JJHl�<^[�Nk��Wg�ЅN��sX��Wg��Ep��;u��Wg��Wg���@��Wg��Wg��6kX:AA                EGG	EGG(EGGlgT��I!��Q+��Q+��Q+��Q+��Q+��Q+��L+��G/��������� ��������������������������������� ���'x���2���1���2���2���2���2���2���2���2���2���2���2���2���2��*��}Y�DFFW?DD*�8eL�5o��sX��Wg�7ee�;ZJn=P=�7fd�3v�ŘD��3v��7h]:AA:AA            EGGEGGEGGRgZ��H ��P*��Q+��Q+��Q+��Q+��Q+��Q+��Q+��O+��D.��������������������������������������� ���8l���-���2���2���2���2���2���2���2���2���2���2���2���2���.��9�jaY�DFF:>CC:AA�6jY�Wg��Ep�9^?:AA#:AA#:AA$�5ox�j]��5ov:AA:AA:AA
            EGGEGG7ZYg�Z8��L'��Q+��Q+��Q+��Q+��Q+��Q+��Q+��Q+��Q+��O+��G.������ ������������������������������ ���TZ���,���2���2���2���2���2���2���2���2���2���2���2���2��~)��}`�EGGVDFF=CC:AA:AA�5mS�8c6:AA:AA:AA:AA:AA�4rp:AA:AA:AA:AA        EGGEGGEGG_fS��J"��R+��Q+��Q+��Q+��Q+��Q+��Q+��Q+��Q+��Q+��Q+��N+��Q.������ ������������������������ ������uA���/���2���2���2���2���2���2���2���2���2���2���2��)�ͅQ�JKJsEGG+CFF:AA:AA:AA	:AA:AA:AA	:AA	:AA	:AA	:AA
:AA:AA	:AA:AA:AA        EGGEGG:YUr�Q-��O)��Q+��Q+��Q+��Q+��Q+��Q+��Q+��Q+��Q+��Q+��Q+��Q+��H-��q)������ ��������������� ������ ���2q���/���2���2���2���2���2���2���2���2���2���2���2���,��D�e\T�EGG:EGGEGG:AA:AA:AA:AA:AA:AA:AA:AA:AA:AA:AA:AA:AA:AA:AA    EGGEGGEGG\jY��I"��Q+��Q+��Q+��Q+��Q+��Q+��Q+��Q+��Q+��Q+��Q+��Q+��Q+��P+��E/������ ������ ��� ������������|��u>���*���0���2���2���2���2���2���2���2���2���2���,��@�n_S�EGGEEGGEGG            :AA:AA:AAEKKEKKEKKEKKEKKEKKEKK                EGGEGG0TT`�X8��N(��Q+��Q+��Q+��Q+��Q+��Q+��Q+��Q+��Q+��Q+��Q+��Q+��Q+��R+��I,��t)������������)w�6e�v5Y�k0P�nQKǉfD֮sI��;���0���/���2���2���1���1���1���1��~)�ޅG�m^R�EGGIEGGIKK	PTTPTTPTTPTTPTTPTTPTTPTT
PTTPTTPTTPTT
PTTPTTPTT            EGGEGGIkb��K#��Q+��Q+��Q+��Q+��Q+��Q+��Q+��Q+��Q+��Q+��Q+��Q+��Q+��Q+��Q+��O+��W*������1v�c>R�CB@�c^Y�tle�yqi�e_Z�CB@�577~NHB��lN��~8��y*��x/��u.��t.��u,��v+��yN�[RL�CEEIEHH!LOOPTTPTTPTTPTTPTTPTTPTTPTTPTTPTTPTTPTTPTTPTTPTTPTT        EGGEGGEGGcfQ��K#��Q+��Q+��Q+��Q+��Q+��Q+��Q+��Q+��Q+��Q+��Q+��Q+��Q+��Q+��Q+��K(��]0���Fp�9;:�rkd�~tk�YOH�B:3�;3,�YOH�~tk�phb�*,,a577x[QH��m?�oE��rS��tX��qU�x`N�577�466R799-AEENRRPTT"PTT(PTT+PTT)PTT&PTT$PTT%PTT*PTT1PTT7S+�hTƣR5�3PTTPTTPTTPTT    EGGEGG-PP\�Y9��O(��Q+��Q+��Q+��Q+��Q+��Q+��Q+��Q+��Q+��Q+��Q+��Q+��Q+��Q+��P)��M(��e\��799~vng�YOH�
�
�
�
�
��oe]�nf`� ""gjd^��}u�oe]�YOH�QHA�YOH�wld��zr�le_�+..6=@@,LPP0S)�uT��UƺT��R8�WPTT<PTT=T��U��V��V��V��V߯R5�2PTTPTTPTT    EGG
EGG=_W��R+��P*��Q+��Q+��Q+��Q+��Q+��Q+��Q+��Q+��Q+��Q+��Q+��Q+��Q+��Q+��L%��bS��>@@v]YT|oe]�
�
�3+%�YOH�JA:�$�
���{r�a[V�wld�$�
�
�,$�
�
�,$��{r�LJGl;:EJS��V��V��U��V��V��T��R=}iV��U��U��U��U��V�S)�JPTTPTTPTT    EGGEGGKf[��M%��Q+��Q+��Q+��Q*��Q)��R)��R)��R)��Q)��Q*��Q+��Q+��Q+��Q+��M&��]>��LLR�9;;Ec]Xhoe]��oe]�}tl�^XS�ha[уyq�,$�
�QHA��{r�$��oe]���y��xp�{r�B:3�
�JA:�tle�H��S��U��U��U��U��U��V��T ��V�U��U��U��V�T��PTT/PTTPTTPTT    EGGEGGXhW��J#��Q(��S$��T%��T*��T0��Q2��N3��P2��T0��S)��T%��S%��Q(��Q+��M'��aS��DFFY577%VQM>~tk�~tk�rjc�Yg�WRM�YOH�
�3+%�h^V�
�QHA�jc]�]UFC?��{s�$���w�F��P��U��VߩVޣV߯U��U��V߯R7��U��U��U��VޣPTTOPTT0PTTPTT        EGGEGGabH��O ��Q6��HT��>m��7}��6���1���-���2���5���8{��@j��IP��R3��R"��V3��XWk�DFF;/11QMHAEB?RGTiQLH�wog�B:3�
�;3,�QHA�
�wld�CA=�@4Pnf`�JA:�
��{r�J��O	��U��S)��PTT�S0��V��U��V��R:��U��U��U��VޣPTTNPTT/PTTPTT        EGGEGGgU8��@c��/���)���'���(���)���*���*���*���(���(���(���(���1���BW��b?��GHK{DFF)%''
(Ab[V�zqiӍ�y�h^V�3+%�
�
�`WO�QHA�
��{r�++)`.>kd]�QHA�
�oe]�W+��O	��U��R7��PTT~R<~�V��U��U��S+��U��U��U��VޣPTTIPTT-PTTPTT        EGGEGGjP|��!���)���+���+���+���+���+���+���+���+���+���+���+���)���$���Us��EGGjDFF!
VQLgwng�`WO�;3,�
�
�
�
�JA:��{r�QHA�
�oe]�MIE�C6Rnf`�JA:�
��{r�I��O	��U��S+��PTTsR;�V��U��U��S+��U��U��U��VޣPTTGPTT+PTTPTT        EGG EGGjD���$���+���+���+���+���+���+���+���+���+���+���+���+���+���%���D���EGGgACC"2xoh�B:3�
�
�
�
�;3,�oe]�nf`�FC?�oe]�
�JA:�oga�  fXEB?��{r�$�
���y�F��P��U��T$��PTTfR9�uV��U��U��S+��U��U��U��VޣPTTLPTT/PTTPTT        EGGEGGiD���&���+���+���+���+���+���+���+���+���+���+���+���+���+���%���J���EGGp@BB'NJEhwld�
�
�3+%�h^V���y�zqi�SOJ�X^�yq�,$�
�YOH���y���y��{r�B:3�
�B:3�vjn�J
��R��U��T"��PTT\R7�mV��U��U��S*��S+��U��U��VޣPTTQPTT3PTTPTTPTT    EGGEGGd>���)���+���+���+���+���+���+���+���+���+���+���+���+���+���(���9���KRV�@BB5&qib�QHA�
�$��xp�NJE�t[MVQMw=;8be^X�wld�$�
�
�
�
�
�3+%��{r�VGf�N��S��U��T �{PTTQPTTOV��U��U��T$��U��U��U��V��S5�nPTT5PTTPTTPTT    EGGEGG\N���$���+���+���+���+���+���+���+���+���+���+���+���+���+���*���)���[q��ACCK%''.ld^�YOH�
�,$�|sk��x itle�oe]�~tk�?<9_nf`��~u�oe]�`WO�QHA�`WO�wld��xp�e`Z�?&pfQ��T��U��T�sPTTAPTT@VޯU��U��UƥU��U��U��U��V��S1�MPTTPTT	PTT    EGGEGGRS��%���+���+���+���+���+���+���+���+���+���+���+���+���+���+���"���Y���CEEo133;A?<^~tk�
�
�h^V��yq�zqj�v�YOH�
�oe]�[VPo48ZUPrmf_�umf�ha[�QMIc ""8/224C/mATرU��V߯R;�>PTT.PTT-U�tV�V��T��U��U��U��U��U��U�xPTTPTT
PTT    EGGEGGCUt��&���+���+���+���+���+���+���+���+���+���+���+���+���+���+���)���,���Yjw�<>>Z$&&Eule�QHA�
�
�$�3+%��
�
�oe]�`ZUh!##(-//./11@.00I+--D'))5"$$%'**9<<HLLQ3�1U�dR5�2PTTPTTPTTPTTS(�HT&�WR;�NT�}UˏVՙVߩV�S)�@PTTPTTPTT    EGGEGG4Pan�0���)���+���+���+���+���+���+���+���+���+���+���+���+���-���.���$���B���HSW�688[;:8avmf�B:3�
�
�
�
�$�`WO�ypi�$&&38::8BDDT`fF�cjD�ILEuACCSACC1BDDHKKOSSPTTPTTPTTPTTPTTPTTPTTPTTPTTPTT&PTT/PTT4PTT4QEn5S,�=PTTPTTPTTPTT    EGGEGG%GKLr?���&���+���+���+���+���+���+���+���+���+���+���*���.���(��������� ���-���FZ_�688hROK�vng�wld�QHA�YOH�oe]��}t�nf`�'))G8::OBDDu��JҚ�������)�L�RTK�EGGHFHH$ILLNQQ	PTT	PTTPTTPTTPTTPTTPTTPTTPTTPTTPTTPTTPTTPTTPTTPTT	PTTPTT    EGGEGGEGGVZ���"���+���+���+���+���+���+���+���+���+���-���-��������� ��� ��� ��� ���$���Kt}�;==�022qKHE�mf`�g`[�TPL�(**_133`;==oY\H���E宻������������	���-�ptS�EGG\EGG+FHHKNNKNNIKKGJJHJJKNNPTTPTTPTTPTTPTT
PTT
PTT
PTT	PTTPTTPTT            EGGEGG<^o~�)���*���+���+���+���+���+���+���+���-���)������ ��� ��� ��� ��� ��� ��� ������.���>x��BSV�:@@�9;;�;=<�GIB�inP���M��)���������������������	�����I�EGGhEGG.EGGEGGEGGEGGEGGEGGEGGEGG                                                EGGEGG%GJJpI���$���+���+���+���+���+���+���-���)������ ��� ��� ��� ��� ��� ��� ��� ��� ��� ���������K���J���8��*���������������������������������������C�EGGkEGG.EGGQTP��VZhnHVEGGHEGG8EGG"EGGEGGEGG                                    EGGEGGEGGJ]z��"���+���+���+���+���+���,���)������ ������ ��� ��� ��� ��� ��� ��� ��� ��� ��� ��������,���	���������������������������������������������	���K�EGGgEGG.EGG'��pz��+霧@�koQ�EGGhEGGGEGG+EGGEGG
EGG                                EGGEGG+JOR|?���&���+���+���+���+���*������ ��� ��� ��� ��� ��� ��� ��� ��� ��� ��� ��� ��� ���m҈���������������������������������������������������������Y�EGG[EGG4EGGI��W������#���:�|�F�NQHEGGVEGG7EGG!EGGEGGEGG                    EGGEGGEGGK_y��#���+���+���*���-������ ��� ��� ��� ��� ��� ��� ��� ��� ��� ��� ��� ��� ��������A����������������������������������������������������������orZ�EGGLEGG>JLKp��H������������/�@�ejL�EGGgEGGFEGG*EGGEGG
EGG                EGGEGG'FHHnP���!���+���-���!������ ��� ��� ��� ��� ��� ��� ��� ��� ��� ��� ��� ��� ���'�����������������������������������������������������������������<�MNMvEGG:EGGFdgT���%���������������"���A�{�L�JMGzEGGOEGG,EGGEGG            EGGEGGEGG=\fm�5���%���,������ ��� ��� ��� ��� ��� ��� ��� ��� ��� ��� ��� ��� ��� ���Dε����������������������������������������������������������������}�[�EGGIEGG+EGGS��U������������������������-�D�rwRwEGG(EGG
                EGGEGGEGGR`z��%���!������ ��� ��� ��� ��� ��� ��� ��� ��� ��� ��� ��� ��� ��� ���YѠ������������������������������������������������������������������@�GIH^EGG"EGG(EGGi��O���������������������������E�EGG:EGG                    EGGEGG%EGGbT}����� ��� ��� ��� ��� ��� ��� ��� ��� ��� ��� ��� ��� ��� ��� ���hя������������������������������������������������������������������%�TVOkEGGEGGEGG6TWO���3������������������������l�EGG6EGG                    EGGEGGEGG-EGGmD��� ��� ��� ��� ��� ��� ��� ��� ��� ��� ��� ��� ��� ��� ��� ���kЇ������������������������������������������������������������������8�MOLYEGGEGGEGGEGGHtxY���������������������P�EGGgEGG#EGG                        EGGEGGEGG1FJLs7������ ��� ��� ��� ��� ��� ��� ��� ��� ��� ��� ��� ��� ���hю���������������������������������������������������������������1�dhN�EGG7EGG    EGGEGG EGG]��W���������������&�fhZ�EGG;EGGEGG                            EGGEGGEGG2EGGnB������ ��� ��� ��� ��� ��� ��� ��� ��� ��� ��� ��� ���[П������������������������������������������������������������;�bfN�EGGDEGGEGG    EGGEGG
EGG.HJIu��I������������W�EGGXEGGEGG                                    EGGEGGEGG.EGGdI������ ��� ��� ��� ��� ��� ��� ��� ��� ��� ��� ���Gг���������������������������������������������������������Q�TWL�EGG@EGGEGGEGGEGGEGGEGGEGGEGG=ceU���%������<�ORM}EGG/EGG
                                            EGGEGGEGG&EGGTPnt�4������ ��� ��� ��� ��� ��� ��� ��� ��� ���)�����������������������������������������������������.���P�EGGgEGG4EGGEGGEGGEGGEGGEGGEGGEGGEGGEGGO��\������f�EGGFEGGEGG                                                EGGEGG	EGGEGG>EGGoU���%��� ��� ��� ��� ��� ��� ��� ��� ��������<������������������������������������������#���O�[_L�EGGNEGG&EGGEGGEGGEGG7XRvQ}o�eJKNEGG    EGGEGG"HJIB��k�MOL@EGGEGG                                                            EGGEGGEGG(EGGLGTWG���/������ ��� ��� ��� ��� ��� ���rс���	���������������������������������(���L�gkO�EGG\EGG4EGGEGGEGGEGG+EGGW\S��\=��rf��EGG$EGG    EGGEGG
EGGEGGEGGEGG
EGG                                                                EGGEGGEGGEGG,EGGLFIJrGz��:������	������ ��� ��������%������������������������,���:耈E�X[J�EGGYEGG7EGGEGGEGGEGGEGG;EGGp`Q��O*��_A��JLO^EGG!EGG        EGGEGGEGGEGGEGG                                                                            EGGEGGEGGEGG&EGG>EGGXEMOvHnw�=���>���=���$���A���+﮺�4?蘡>↎A�tyP�TXK�EGGaEGGFEGG.EGGEGGEGGEGGEGGEGGCPLh�`I��O(��H ��k^��EGGNEGGEGG                                                                                                                EGGEGGEGGEGGEGG&EGG7EGGFEGGSEGG^EGGeCKLlFHGkIKElEGGfEGG_EGGVEGGIEGG;EGG+EGGEGGEGGEGG        EGG	EGG(j]��S2��M&��N(��X5��XWh�EGG5EGG
                                                                                                                                EGGEGGEGGEGGEGGEGGEGGEGGEGG EGGEGGEGGEGGEGGEGG
EGGEGG                    EGG
GHK+dN��S1��L&��H!��kX��EGGbEGGEGG                                                                                                                                                                                                                        EGGEGGEGGGXSu�_G��R+��d\��EGG>EGG                                                                                                                                                                                                                            EGGEGG
EGGEGGAOLdjgR��WToSEGG!EGG                                                                                                                                                                                                                                    EGGEGGEGGEGG&EGGEGGEGG                                                                                                                                                                                                                                        EGGEGGEGGEGGEGG                                                        ������������������� ������ �����   ����   ����   ����   ���      �       �       �       �       �       �       �       �       �       �       �       �     ��      �                                                                                                                             �     ��      ��      ?�      �      �       �       �       �       �       �       �      �      ��     ��    ��    ��    ��    ����  ����� �����������������������������?��%      �� ��             (   0   `                                                                                                                                                                                                                                                                                                                                                                                                                                                                                          EGGEGGEGGEGG+EGG8EGG?EGG@EGG=EGG6EGG*EGGEGG
EGG                                                                                                                                EGGEGG
EGGEGG;nI^p�Iq��?y��-|��*���.���i\�}F�tSԏjQ�iXJkEGG:EGGEGG	EGG                                                                                                            EGGEGGEGG(^IUc�=k��.{��!������ ��� ��� ��� ���"w���3���-���7�߀?�zN�hL�[QJ_EGG)EGGEGG                                                                                                EGGEGG VIQ^�Et��"���	��� ��� ��� ��� ������ ��� ��� ���]Q���,���/���.���-���1�߀@�sT�\RJaEGG EGG            :AA:AA:AA:AA:AA:AA:AA:AA:AA:AA                                    EGGEGG:�Hl��)������ ��� ������������������������ ���;i���-���2���2���2���1���/���/�ڀB��iS�EGG:EGGEGG:AA:AA:AA:AA:AA:AA:AA:AA:AA:AA:AA:AA                        EGGEGGPHMS�D|����� ��� ������������������������������ ���%w���1���2���2���2���2���2���2���.���4��xV�[RKZDGG<BB:AA:AA�4sm:AA:AA:AA:AA�4sm:AA:AA:AA                        EGGWK_e�5��� ��� ~����������������������������������� ������6���1���2���2���2���2���2���2���/���,��M�]SLdAEE:AA�4qs����5pu:AA#:AA#�5pu����4qs:AA:AA                    EGGLLW[bF��]%��v$��������� ������������������������������ ������|6���0���2���2���2���2���2���2���2���0���*��Q�FHGD�8b9�4q�����5o��5m}�7fc�5o�����5p��6lV:AA                EGG
EGGHcP��H#��L+��G-��H/���#���	��� ��������������������������� ������7���0���2���2���2���2���2���2���2���2���.��=�yNWt�Ep��sX�ŘD��sX��j]��Wg��sX�ŘD��sX��Wg��5pN            EGGEGG4dX��L%��P*��R+��R+��O+��@/��h)������ ������������������������ ��� |���4���1���2���2���2���2���2���2���2���3��*�ŀO�CFFE�8a8�4q��sX��5p��5m{�7fb�5p��sX��4q��6lU:AA            EGGe_��P+��L&��Q+��Q+��Q+��Q+��Q+��C.��c)���
��� ��������������������� ���1p���/���2���2���2���2���2���2���2���3���/���/��s`�BFF#:AA�8b7�Ep�9`::AA:AA�9`:�Ep�8b7:AA:AA
        EGGLLRPhR��I!��Q+��Q+��Q+��Q+��Q+��Q+��R+��F-��s'������ ������������������ ���O[���,���2���2���2���2���2���2���2���1��~'���\�EGG?@DD:AA	:AA�7h/:AA:AA:AA:AA�7h/:AA:AA	:AA        EGGaW��L%��P)��Q+��Q+��Q+��Q+��Q+��Q+��Q+��Q+��B/������ ��� ��� ��� ��� ��� ������t=���.���2���2���2���2���2���2���1��)�҃K�b\VfEGG:AA:AA:AA:AA:AA:AA:AA:AA:AA:AA:AA:AA    EGGFHIIdN��I"��R,��Q+��Q+��Q+��Q+��Q+��Q+��Q+��Q+��J,��U-������ �����������}��X[��2���.���/���2���2���2���2���0��*�؂E�k^SzEGGEGG            EKKPTTPTTPTTPTTLPPPTT        EGGEGGc^�S/��P*��Q+��Q+��Q+��Q+��Q+��Q+��Q+��Q+��Q+��Q+��E/������{��1l�sJ\�sbb�qda�aVL�rXA��oJ��:��}+��~0��|0��|-��|-��N�eYOwGII NRRPTTPTTPTTPTTPTTPTTPTTPTTPTTPTTPTTPTT    EGGVUiDeX��L#��Q+��Q+��Q+��Q+��Q+��Q+��Q+��Q+��Q+��Q+��P*��C(���;��uX`�~un�oe]�QHA�QHA�wld�xoh�VRN�`QD��rJ�vY��xa��sX��l[�MHC|799.FJJPTTPTT'PTT)PTT(PTT&PTT(PTT0S-�RT��UʎR7�(PTTPTT    EGGa\��`I��L%��Q+��Q+��Q+��Q+��Q+��Q+��Q+��Q+��Q+��Q+��J$��WD��WKX��{r�3+%�
�
�
�
�B:3�tle�rkd�~tk�QHA�B:3�QHA�YOH��{r�le_�D3e>UƥU��V	��UҿT&�pS*�hU��V��V��U��U�hPTTPTT    EGG"dW��[:��N'��Q+��Q*��Q)��R)��R)��Q)��Q+��Q+��Q+��O(��S0��]Z}�c^Yooe]�
�QHA�wld�wld�3+%�
�h^V�oe]�
�$�JA:�;3,�
�3+%��wo�J��T��U��U��U��V��UŗU��U��U��U��T�nPTTPTT    EGG1dR��V1��P!��T%��S+��R2��O3��P3��S0��S)��T%��S&��L#��cO��BDDGg`ZIwld�oe]�tle�A>;�OKG�~tk�
�JA:�3+%�$��{r�pha�yph�oe]�
�oe]�Z*��S��U��V�U��U��V߯U��U��U��UǓQCrDPTTPTT    EGG;\=��U0��GL��=l��5��3���.���0���3���8y��@c��L?��R%��cZ��ACC"`ZTN[UPpHEAsjc\�vn�YOH�
�QHA��JA:�oga�:L��y�
�`WO�`9��R��UɝR=|�V߾U��V��S,��U��U��UȒPTT9PTTPTT    EGGANX��8y��(���'���(���)���*���*���(���(���'���(���Gg��ZQw�@BB^XS[xoh�wld�QHA�,$�
��wld�
�YOH�f_Y�+?��y�
�YOH�eA��R��UÙPTT~VߺU��U��S,��U��U��UɑPTT5PTTPTT    EGGCC���*���(���+���+���+���+���+���+���+���+���%���6���J\p�:<<zqi�B:3�
�
�
�;3,�~tk�zqj�3+%�B:3�skd�RMI�a[U�~tk�
�oe]�X*��S��UƕPTTkVߺU��U��S,��U��U��UɑPTT8PTTPTT    EGG@?���-���*���+���+���+���+���+���+���+���+���'���4���Sgv�8::b\Vdoe]�
�$�h^V���y�{rj�UPK�_YS�`WO�
�QHA�oe]�h^V�,$�$��{r�O��T��UɑPTTZV	ٟU��U��T(��U��U��UǓPTT<PTTPTT    EGG:C���.���)���+���+���+���+���+���+���+���+���*���'���Zw��=??(oha�`WO�
�YOH�[VQ�qd^X��{r��{r�vmf�`WO�3+%�3+%�3+%�;3,�wld�nY{�P��U��U͌PTTIU̎U��U��V��U��U��V��U�yPTTPTT    EGG/N���2���(���+���+���+���+���+���+���+���+���,���"���T���CEEL.��w��;3,��~v��vn�wld�,$�oe]�ZTOqmf_��zr݄zr�yqހwo�e_ZuC"�UTټV��T �\PTT1T"�_V��V�V��U��U��U��VޣPTTPTT    EGG Sx��9���'���+���+���+���+���+���+���+���+���+���+���0���\u��355;vmf�YOH�
��,$�
�
�wld�\VQT-//(355@133D*,,0#%%144EHHS �?U�PPTTPTTPTTT�XS.�TS'�iUˏVޣV�U�pPTTPTT    EGGXn~yG���%���+���+���+���+���+���+���+���+���.���)������*���Imt�9:9Jypi�~tk�B:3�,$�B:3�~tk�|sk�466:hmG���8ނ�<�mrK�EGG>HJJOSS
PTTPTTPTTPTTPTTPTTPTTPTT%PTT+PTT+S,�=PTTPTTPTT    EGGT_f>Z���#���+���+���+���+���+���+���-���-��������� ��� ������H~��8::bUQMyypiÄzr�yqi�VRNw9;;]v}J���+���
���������E�Z]KpFHH JMMPTTMQQMQQPTTPTTPTTPTTPTTPTTPTTPTT
PTTPTT    EGGEGG[jw�0���)���+���+���+���+���.���*������ ��� ��� ��� ��� ������(���B���Ago�Z`C�dhD�~�NǦ�A���������������������-�dhG�EGG$EGG`dZdjL#EGGEGGEGG        PTTPTTPTT                EGGEGGBP���!���,���+���+���-���*������ ��� ��� ��� ��� ��� ��� ��� ��� ���f͓���(��� ���������������������������
���$�ilJ�EGG"EGG��\���;�WZKgEGG1EGGEGG                                EGG[r��)���(���+���,���+������ ��� ��� ��� ��� ��� ��� ��� ��� ���&��������
������������������������������������,�hkV�EGG%��as��4���*���>�hmJ�EGGAEGGEGG	EGG                    EGGEGGDT������+���-������ ��� ��� ��� ��� ��� ��� ��� ��� ��� ���]љ���
������������������������������������������A�NPNQEGG1��g���������#���9�{�H�X\HbEGG.EGGEGGEGG            EGGbqz�8���&���$������ ��� ��� ��� ��� ��� ��� ��� ��� ��������j���	������������������������������������������	���c�EGG(EGG=��L���������������5���A�lqI�[_LBEGG            EGGEGG.a��'������ ��� ��� ��� ��� ��� ��� ��� ��� ��� ���
�����P���
���������������������������������������������9�JLJCEGGRUK]��=������������������)���I�EGG"                EGGEGGAK}����� ��� ��� ��� ��� ��� ��� ��� ��� ��� ��������D������������������������������������������������"�]_UYEGGEGGru[���%���������������9�h�EGG                    EGGGMOO>��� ��� ��� ��� ��� ��� ��� ��� ��� ��� ��������B������������������������������������������������D�EGG3EGGEGGEGG/��T���������������`�EGG0EGG                        EGGFNPO6������ ��� ��� ��� ��� ��� ��� ��� ��������M���������������������������������������������H�MPIPEGG        EGG	EGGI��R���������J�EGGFEGG                                EGGEGGBE������ ��� ��� ��� ��� ��� ��� ��������`���	������������������������������������%���Q�EGGCEGGEGGEGGEGGEGGEGGbdVy��&���#�ps[�EGG                                        EGG	EGG.Jrz�4������ ��� ��� ��� ��� ��� ���jщ���	���������������������������������A�puM�EGG/EGG	EGGEGG]W~8lh�EGGEGGEGG&��b���b�EGG1EGG                                            EGGEGGFMOHK��4������ ��� ��� ��� ���7����������������������������� ���>�|�N�PSIMEGGEGGEGGEGG=^P��kXʾ_]m4EGG    EGGLNKPRMEGG
                                                        EGGEGGEGGDKt}�8���&��������������e������������!���+���;퍘=�ntI�EGGEEGGEGGEGGEGGIHW[YG��N(��pd��EGG$EGG                                                                                    EGGEGGEGG+EKLIDksxB~��9���3���x�<ǅ�3Ā�B�w}A�fkIwIKHIEGG+EGGEGG        EGG]R��[A��J#��[<��WVfsEGG                                                                                                    EGGEGGEGGEGGEGG"EGG#EGG"EGGEGGEGGEGG                    EGGdN��L%��G��jZ��EGG6EGG                                                                                                                                                                    EGGIITG^S��Z=��aZ��EGG                                                                                                                                                                            EGG
OMa?dQ��]X|FEGG	                                                                                                                                                                            EGGEGG
EGGEGGEGG                                        ������  ������  �� ��  �� ��  ��  �  ��  8  �       �       �       �       �       �       �       �       �       �                                                                                                            �  �    ?  �      �       �       �       �       �       �     �      �      ��   �  ��   �  �� �  �� �  �����  ������  ������  �      �� ��             (       @                                                              EGGEGGEGG
EGGEGGEGGEGGEGGEGGEGGEGGEGG                                                                        EGGEGGEGGEGG#EGG8EGGLEGG\EGGeEGGgEGGbEGGVEGGEEGG1EGGEGGEGGEGG    :AA:AA:AA:AA:AA:AA:AA:AA                EGGEGGEGGEGG(EGGGEGGkyC`��Bw��,������0|��zI��{K�jL�eVL�EGG`EGG=EGG DGG@DD:AA:AA:AA	:AA	:AA	:AA	:AA:AA            EGGEGG
EGGEGG@FGHq�Cn��$������ ��� ��� ��� ���H[���)���0��8��xF�cN�EGG`EGG5CFF?DD:AA:AA:AA:AA:AA:AA:AA        EGGEGG
EGG$EGGS|Ke��'������ ��� ��� ��������� ���$v���0���1���0���.���2��yM�[SL�DFFFBEE#�=V$�4t~}<T'}<T'�4t~�;X :AA    EGGEGG
EGG%EGG[�Fw����� ~�� ������������������ ������6���0���2���2���1���-�ށB�s^P�CFFC�6o�����4r��4r�����4t~�:[    EGGEGGEGGU`U��[(��u"������ ������������������ ������}7���0���2���2���2���2���+���D�E_��g[�ŘD��j]��Wg�ŘD��sX��3uzEGGEGGEGGC]Y~�R/��K(��G-��I.��������� ������������ ������6���0���2���2���2���2���-��A�OLIf�8i}�Wg��5pu�6me�Wg��4t}�:\EGG	EGG,NOV{]?��K$��Q+��Q+��N+��D/������ ������������ ���'t���0���2���2���2���2���1���*��z_�DGGPBFF%�6lU=DD=DD�6lU<CC<BBEGGEGGOdV��K$��Q+��Q+��Q+��Q+��N+��I.������}��~��{�����HR���+��1��1��1��1��{*��R�GIIsFII9FKK"EKKEKK DJJCIIBHHAGGEGG)NNU{]>��M&��Q+��Q+��Q+��Q+��Q+��G-��n#���{��s��@n�Rf�j@��r0��q*��u.��u.��u,��tF�PNJ�FHHMJNN0MQQ(LQQ)LQQ(LPP#JOOINNINNEGG@aZ��O(��Q+��Q+��Q+��Q+��Q+��Q+��K)��T*���_s�{r�h^V�`WO��{r�ncZ�kQ��{i��|j��ue�XUQ�>@@`I1{VR-�SQHiAR>{GT�nVդT�OOSSPTTEGGTcS��L$��Q*��R)��R)��Q)��Q*��Q+��I&��cU��~tk��$��$��{r�h^V�3+%�3+%�B:3��{r�M!��Q��U��V��V��U��U��V�S)�8PTTEGGc`B��O ��R,��Q2��O3��R/��S'��O ��[@��SPO�wld�YOH��{r�~v�$�RIB�
�oe]�~tk�3+%�YOH�g@��N	��S��U��V�U��U��U�}PTT'PTTEGGkSD��:h��3���0���.���1���7w��AJ��`O��688yKHE{phbƍ�y�`WO��NE>�3+%�zqj�VRM�`WO�;3,�w]��L	��Q��U��V��U��U��T�uPTT+PTTEGGo9���%���)���*���*���)���(���'���K^��244qumf�JA:�
�
�JA:�j`X�,$��vn�kd^�YOH�JA:�oO��L	��Q��U��V��U��U��T�uPTT,PTTEGGm6���)���+���+���+���+���+���&���Lr��XUQ�oe]�
�`WO���y�jc\ցwo�,$�;3,�JA:��oe]�[)��N��Q��U��V��V��U��U��PTT*PTTEGGe?���'���+���+���+���+���+���$���I���HHF�~tk�
�wld���y�JA:�wld��zr�oe]�oe]�~tk�t^�M	��QѸQ'�nV��V��U��U��V��T&�EPTTEGGXJ���%���+���+���+���+���+���,���+���Hgt�ske�QHA�
�
�$�~tk�BB@�`^O�[XR�LJH|>-a]L�|L-�GOSS2T#�aU�qVۜVߩV߯S0�+PTTEGGEYz��$���+���+���+���,���-������������Eox�qjd�~tk�oe]��|t�lg_�|�9������)�inH�BDDnDFFCILL-LOO-LPP2MQQ/ORR)QAu*S0�+PTTPTT
EGG/R[b�6���'���+���,���,������ ��� ���������"���I{��twO恇>奰.�������������}�<�FHHrHLKHrzMWHJJHHJJGIKK8JMM'LOOMQQPTTEGGEGGYS���!���,���,������ ��� ��� ��� ���������s�j���������������������������I�EGG{��`���4�~�E�JLHvFHHWFII9FIIHJJEGGEGG5V`g�7���(������ ��� ��� ��� ��� ��� ��������(���������������������������
�ux`�FHH���C������-�B�aeH�EGGIEGGEGGEGGEGGOb}��!������ ��� ��� ��� ��� ��� ���1�����������������������������������9�HJI�]`P���'������������B�EGG4    EGGEGG%EGGcD��� ��� ��� ��� ��� ��� ��� ���=ϼ���������������������������������#�TVOwEGGh�X������������[�EGG:    EGGEGGEGG-EGGj5������ ��� ��� ��� ��� ���9��������������������������������$�|�M�EGGLEGG;EGGh��U���	���4�TVPzEGG,        EGGEGGEGG.EGGdE������ ��� ��� ��� ���%�����������������������������3�ouL�EGGeEGG=EGG)EGG<TVPm��7⒘`�EGGDEGG            EGGEGGEGG&EGGQHel�<������ ��� ��������=������������������.�I�KNH�EGGmEGG_aO��xp�TEGG&EGG,nq]HOQM4EGGEGG                EGGEGG	EGGEGG6EGGZIbg�;���.��� ���O��������)�2옢D�xC�NQHxEGGTEGGLNKakV;��cE��YYgJEGGEGGEGGEGGEGGEGG                        EGGEGGEGGEGG0EGGFEGGYEHHhBQTtMRFvKMFpEGGcEGGSEGG>EGG(EGGEGG3cIջE��pa��EGG<EGGEGGEGGEGG                                        EGGEGGEGGEGGEGGEGG#EGG$EGG"EGGEGGEGGEGGEGG	EGG!VNzWfOͭ`Y�bEGG'EGG
                                                                        EGGEGGEGG                EGGEGGEGG!EGG*EGG EGGEGG                    � ��  �   �   �   �   �                                                                       �   �   �   �   �   �  �  ���h      �� ��             (                                                 EGGEGGEGG9EGGJEGGLEGG@EGG'EGGEGG                    EGGEGGJGJJ�<i��(|�����Ah�Ӂ?�nH�dUJnDGG'@DD:AA	:AA	:AAEGGEGG]Jgx�)|�� ��� ��� ���~���2���-��;��lR�nAR;�4sn�4r^�6i-EGGUTdkZ;��x������ ��� ������}8���0���,��;��:o�����"���,}�NOWGfU��H"��C.��f(���������6r���.���0��+��}Z�sDVc�1y��1y�;e5d[��U0��P&��R*��?,���=��wld�wld��v_��zf��sj�`@��S��j!��f��O)�0ZA��Q+��O3��N+��^A��wld�;3,�3+%�F=7�;3,�B:3�tW��U��U��U��U�oAb��2��.���,���Og��ga[�YOH�,$�.& �{rj�;3,�w^��U��V��V��S)�K6���)���*���&���O���wld�;3,�wld�dZS�B:3�YOH�i@��V��U��U��U�nL~��*���+���,���!���c{}�QHA�B:3��{r��{c�o_r�S��R*�kS�zVޯS(�,\q��=���'������ ������d�����_���4�������dhT���Q�jpFK;j[HKK%EGG-_{����� ��� ��� ���p�{���������������C섇b��� ���3熏A�EGGEGG@6��� ��� ��� �����i���������������/�EGGu��L������[�    EGGEGG@>������ ���fϊ���
������!���7�TVP�[U{]\]XW��`�ehYH        EGGEGG'FX\`9���;��΅�8҃�<�ejF{EGGX[Aȷrb��EGG EGGEGG	            EGGEGGEGGEGG%EGG'EGGEGGEGG _H��d\�XEGG        �  �                                               �   �   �  >   0   �� I C O N _ L O G O       0            @@     (B   00     �%          �        h     *  @   T R A N S L A T O R   L A N G _ C N         0         <?xml version="1.0" encoding="utf-8"?>
<language name="简体中文" guid="{0DAEDE3C-6B94-4a81-9A55-C304FDD69D98}">
  <context>
    <!--没有上下文的翻译-->
  </context>
  <context name="messagebox">
    <message>
      <source>ok</source>
      <translation>确定</translation>
    </message>
    <message>
      <source>cancel</source>
      <translation>取消</translation>
    </message>
    <message>
      <source>retry</source>
      <translation>重试</translation>
    </message>
  </context>

  <context name="dlg_setup">
    <message>
      <source>Chinese</source>
      <translation>中 文</translation>
    </message>
    <message>
      <source>English</source>
      <translation>英 语</translation>
    </message>
  </context>

  <context name="MenuCtx">
    <message>
      <source>Clear</source>
      <translation>清屏</translation>
    </message>
    <message>
      <source>Copy</source>
      <translation>复制</translation>
    </message>
    <message>
      <source>Cut</source>
      <translation>剪切</translation>
    </message>
    <message>
      <source>Revoke</source>
      <translation>撤回</translation>
    </message>
    <message>
      <source>Select all</source>
      <translation>全选</translation>
    </message>
    <message>
      <source>Save as</source>
      <translation>另存为</translation>
    </message>
    <message>
      <source>Save as</source>
      <translation>另存为</translation>
    </message>
    <message>
      <source>Open</source>
      <translation>打开</translation>
    </message>
    <message>
      <source>Open folder</source>
      <translation>打开文件夹</translation>
    </message>
    <message>
      <source>Send message</source>
      <translation>发送消息</translation>
    </message>
    <message>
      <source>Network call</source>
      <translation>网络通话</translation>
    </message>
    <message>
      <source>View more</source>
      <translation>查看资料</translation>
    </message>
    <message>
      <source>Copy(&C)</source>
      <translation>复制(&C)</translation>
    </message>
    <message>
      <source>Cut(&X)</source>
      <translation>剪切(&X)</translation>
    </message>
    <message>
      <source>Paste(&V)</source>
      <translation>粘贴(&V)</translation>
    </message>
    <message>
      <source>Select all(&A)</source>
      <translation>全选(&A)</translation>
    </message>
  </context>

  <context name="dlg_main">
    <message>
      <source>close</source>
      <translation>关闭窗口</translation>
    </message>
    <message>
      <source>Send</source>
      <translation>发 送</translation>
    </message>
  </context>

  <context name="dlg_login">
    <message>
      <source>close</source>
      <translation>关闭窗口</translation>
    </message>
    <message>
      <source>Password</source>
      <translation>输入密码</translation>
    </message>
    <message>
      <source>Employee number</source>
      <translation>输入工号</translation>
    </message>
    <message>
      <source>Keep Password</source>
      <translation>记住密码</translation>
    </message>
    <message>
      <source>Auto Login</source>
      <translation>自动登录</translation>
    </message>
    <message>
      <source>Login</source>
      <translation>登      录</translation>
    </message>
  </context>

  <context name="dlg_userInfo">
    <message>
      <source>close</source>
      <translation>关闭窗口</translation>
    </message>
    <message>
      <source>Emp No</source>
      <translation>工 号</translation>
    </message>
    <message>
      <source>Dept</source>
      <translation>部 门</translation>
    </message>
    <message>
      <source>Phone</source>
      <translation>手 机</translation>
    </message>
    <message>
      <source>Contact him\her</source>
      <translation>与他\她联系</translation>
    </message>
  </context>

</language>
  �  @   T R A N S L A T O R   L A N G _ J P         0         ﻿<?xml version="1.0" encoding="utf-8"?>
<language name="日本语" guid="{23D209C4-2268-49A2-B7F4-8CB57D908D47}">
  <context>
    <!--没有上下文的翻译-->
  </context>
  <context name="messagebox">
    <message>
      <source>ok</source>
      <translation>確定</translation>
    </message>
    <message>
      <source>cancel</source>
      <translation>キャンセル</translation>
    </message>
    <message>
      <source>retry</source>
      <translation>リトライ</translation>
    </message>
  </context>
  <context name="dlg_main">
    <message>
      <source>close</source>
      <translation>窓を閉じて</translation>
    </message>
    <message>
      <source>lang_cn</source>
      <translation>簡体字</translation>
    </message>
    <message>
      <source>lang_jp</source>
      <translation>日本語</translation>
    </message>
    <message>
      <source>这是一个由SOUI向导生成的APP框架</source>
      <translation>これはSOUIガイド生成のAPPフレーム</translation>
    </message>
    <message>
      <source>mainpage</source>
      <translation>ホームページ </translation>
    </message>
    <message>
      <source>page2</source>
      <translation>ページ2</translation>
    </message>
    <message>
      <source>页面1</source>
      <translation>ページ1</translation>
    </message>
  </context>
</language>   �  @   T R A N S L A T O R   L A N G _ E N         0         <?xml version="1.0" encoding="utf-8"?>
<language name="English" guid="{0DAEDE3C-6B94-4a81-9A88-C304FDD69D96}">
  <context>
    <!--没有上下文的翻译-->
  </context>
  <context name="messagebox">
    <message>
      <source>ok</source>
      <translation>ok</translation>
    </message>
    <message>
      <source>cancel</source>
      <translation>cancel</translation>
    </message>
    <message>
      <source>retry</source>
      <translation>retry</translation>
    </message>
  </context>

  <context name="dlg_setup">
    <message>
      <source>Chinese</source>
      <translation>Chinese</translation>
    </message>
    <message>
      <source>English</source>
      <translation>English</translation>
    </message>
  </context>

  <context name="MenuCtx">
    <message>
      <source>Clear</source>
      <translation>Clear</translation>
    </message>
    <message>
      <source>Copy</source>
      <translation>Copy</translation>
    </message>
    <message>
      <source>Cut</source>
      <translation>Cut</translation>
    </message>
    <message>
      <source>Revoke</source>
      <translation>Revoke</translation>
    </message>
    <message>
      <source>Select all</source>
      <translation>Select all</translation>
    </message>
    <message>
      <source>Save as</source>
      <translation>Save as</translation>
    </message>
    <message>
      <source>Save as</source>
      <translation>Save as</translation>
    </message>
    <message>
      <source>Open</source>
      <translation>Open</translation>
    </message>
    <message>
      <source>Open folder</source>
      <translation>Open folder</translation>
    </message>
    <message>
      <source>Send message</source>
      <translation>Send message</translation>
    </message>
    <message>
      <source>Network call</source>
      <translation>Network call</translation>
    </message>
    <message>
      <source>View more</source>
      <translation>View more</translation>
    </message>
    <message>
      <source>Copy(&C)</source>
      <translation>Copy(&C)</translation>
    </message>
    <message>
      <source>Cut(&X)</source>
      <translation>Cut(&X)</translation>
    </message>
    <message>
      <source>Paste(&V)</source>
      <translation>Paste(&V)</translation>
    </message>
    <message>
      <source>Select all(&A)</source>
      <translation>Select all(&A)</translation>
    </message>
  </context>

  <context name="dlg_main">
    <message>
      <source>close</source>
      <translation>close</translation>
    </message>
    <message>
      <source>Send</source>
      <translation>Send</translation>
    </message>
  </context>

  <context name="dlg_login">
    <message>
      <source>close</source>
      <translation>close</translation>
    </message>
    <message>
      <source>Password</source>
      <translation>Password</translation>
    </message>
    <message>
      <source>Employee number</source>
      <translation>Employee number</translation>
    </message>
    <message>
      <source>Keep Password</source>
      <translation>Keep Password</translation>
    </message>
    <message>
      <source>Auto Login</source>
      <translation>Auto Login</translation>
    </message>
  </context>

  <context name="dlg_userInfo">
    <message>
      <source>close</source>
      <translation>close</translation>
    </message>
    <message>
      <source>Emp No</source>
      <translation>Emp No</translation>
    </message>
    <message>
      <source>Dept</source>
      <translation>Dept</translation>
    </message>
    <message>
      <source>Phone</source>
      <translation>Phone</translation>
    </message>
    <message>
      <source>Contact him\her</source>
      <translation>Contact him\her</translation>
    </message>
  </context>

</language>
  7  8   S M E N U   M E N U _ T R A Y       0         ﻿<menu iconSkin="skin_traymenu_icons" itemHeight="26" iconMargin="4" textMargin="8">
  <item id="1" check="1">导出配置</item>
  <item id="2" radio="1">导入配置</item>
  <item id="3" disable="1">检查更新</item>
  <item id="4">这是测试菜单1</item>
  <sep/>
  <item id="5">
    帮助与反馈
    <item id="51" icon="0">访问官网</item>
    <item id="52" icon="1">帮助指南</item>
    <item id="53" icon="2">错误提交</item>
    <item id="54" icon="3">关于SOUI</item>
  </item>
  <sep/>
  <item id="6">退出</item>
</menu> �   @   S M E N U   M E N U _ T E M P L A T E       0         <menuRoot skin="skin.menu_bkg" margin="5,5,5,5" textOffset="10" itemHeight="30" iconBarWidth="32" minWidth="180" maxWidth="400" trCtx="MenuCtx"/>

 