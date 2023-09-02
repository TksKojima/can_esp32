(function(){"use strict";var t={1373:function(t,e,s){var i=s(144),a=s(998),n=s(3059),l=function(){var t=this,e=t._self._c;return e(a.Z,[e(n.Z,[e("router-view")],1)],1)},c=[],o={name:"App",data:()=>({})},r=o,d=s(1001),u=(0,d.Z)(r,l,c,!1,null,null,null),_=u.exports,h=s(8345),p=s(266),g=s(9256),m=s(1713),f=s(9884),v=s(7808),x=function(){var t=this,e=t._self._c;return e("div",[e(g.Z,[e(m.Z,[e(p.Z,{attrs:{cols:"12",sm:"2"}},[e(m.Z,[e(p.Z,{attrs:{cols:"6",sm:"12"}},[e(f.Z,{attrs:{label:"CAN受信"},on:{click:function(e){return t.websocketconnect()}},model:{value:t.toggle_rx_msg,callback:function(e){t.toggle_rx_msg=e},expression:"toggle_rx_msg"}})],1),e(p.Z,{attrs:{cols:"6",sm:"12"}},[e(v.Z,{attrs:{label:"IDフィルタ",placeholder:"ex: 0x01, 0x0Y-0x0X, 0xZZ"},on:{blur:function(e){return t.idFilterInput(t.idfilter_val)}},model:{value:t.idfilter_val,callback:function(e){t.idfilter_val=e},expression:"idfilter_val"}})],1)],1),e(m.Z,[e(p.Z,{attrs:{cols:"5",sm:"12"}},[e(f.Z,{attrs:{label:`自動ソート: ${t.sortTargetStr()}   `},model:{value:t.toggle_sort,callback:function(e){t.toggle_sort=e},expression:"toggle_sort"}})],1),e(p.Z,{attrs:{cols:"4",sm:"12"}},[e(f.Z,{attrs:{label:"16進表示"},model:{value:t.toggle_hex,callback:function(e){t.toggle_hex=e},expression:"toggle_hex"}})],1),e(p.Z,{attrs:{cols:"3",sm:"12"}},[e(v.Z,{staticClass:"centered-input",attrs:{value:t.timecnt,label:"動作カウント",disabled:""}})],1)],1)],1),e(p.Z,{attrs:{cols:"12",sm:"10"}},[e("table",{staticClass:"canrecv_table",attrs:{"aria-describedby":"listhelp"}},[e("thead",{staticClass:"canrecv_th"},[e("tr",[e("th",{staticClass:"canrecv_th",staticStyle:{cursor:"pointer"},on:{click:function(e){return t.sortMsg(0,1)}}},[t._v("ID "+t._s(t.sort_direction_str[0])+" ")]),e("th",{staticClass:"canrecv_th",staticStyle:{cursor:"pointer"},on:{click:function(e){return t.sortMsg(1,1)}}},[t._v("dlc "+t._s(t.sort_direction_str[1])+" ")]),e("th",{staticClass:"canrecv_th",staticStyle:{cursor:"pointer"},on:{click:function(e){return t.sortMsg(2,1)}}},[t._v("time"+t._s(t.sort_direction_str[2])+" ")]),e("th",{staticClass:"canrecv_th"},[t._v("data0")]),e("th",{staticClass:"canrecv_th"},[t._v("data1")]),e("th",{staticClass:"canrecv_th"},[t._v("data2")]),e("th",{staticClass:"canrecv_th"},[t._v("data3")]),e("th",{staticClass:"canrecv_th"},[t._v("data4")]),e("th",{staticClass:"canrecv_th"},[t._v("data5")]),e("th",{staticClass:"canrecv_th"},[t._v("data6")]),e("th",{staticClass:"canrecv_th"},[t._v("data7")]),e("th",{staticClass:"canrecv_th"},[t._v("delay")])])]),e("tbody",t._l(t.id_num,(function(s,i){return e("tr",{key:s},[e("td",{staticClass:"canrecv_td",style:{color:t.colorStr(t.can_msgs[i].updatecount)},attrs:{scope:"row"}},[t._v(" "+t._s(t.toggleDecOrHex(t.can_msgs[i].id)))]),e("td",{staticClass:"canrecv_td",style:{color:t.colorStr(t.can_msgs[i].updatecount)}},[t._v(" "+t._s(t.can_msgs[i].dlc))]),e("td",{staticClass:"canrecv_td",style:{color:t.colorStr(t.can_msgs[i].updatecount)}},[t._v(" "+t._s(t.can_msgs[i].cycle))]),t._l(8,(function(s){return e("td",{key:s,staticClass:"canrecv_td",style:{color:t.colorStr(t.can_msgs[i].updatecount_data[s-1])}},[t._v(" "+t._s(t.toggleDecOrHex(t.can_msgs[i].data[s-1]))+" ")])})),e("td",{staticClass:"canrecv_td"},[t._v(" "+t._s(t.can_msgs[i].updatecount))])],2)})),0)])])],1)],1)],1)},b=[],y=(s(7658),s(2003)),D={beforeRouteLeave(t,e,s){this.$destroy(),s()},data(){return{selectItem:{name:"",mac:""},can_dlc:0,can_msgs:[],can_msg:{id:0,dlc:0,data:[0,0,0,0,0,0,0,0],cycle:-1,updatetime:0,updatecount:-1,updatecount_data:[0,0,0,0,0,0,0,0]},onrec_time:0,timecnt:0,myStyle:"RGB(10,0,200)",id_num:0,sort_direction_id:1,sort_direction_dlc:1,sort_direction_time:1,sort_direction_str:["↑↓","↑↓","↑↓"],sort_target:-1,sort_target_str:["ID","dlc","time"],sort_cnt:0,connect_status:-1,toggle_sort:!1,toggle_rx_msg:!1,toggle_hex:!1,idfilter_val:"",idfilter_list:[],enable_rx_msg:!0,lastInterval:0}},mounted(){for(let t=0;t<2047;t++)this.can_msg.id=-1,this.can_msgs[t]=Object.assign({},this.can_msg)},computed:{},methods:{toggleDecOrHex:function(t){if("0"==t)return 0;if(0==t)return 0;if(null==t)return"";if(""==t)return"";let e=Number(t);return this.toggle_hex?e.toString(16):e},colorStr:function(t){var e=2*t;e>10&&(e=10);var s=e.toString(16);return"#"+s+s+s},sortTargetStr:function(){return this.sort_target>=0?this.sort_target_str[this.sort_target]:"(未)"},websocketconnect:function(){console.log("Starting connection to WebSocket Server"),console.log("can rx test"),console.log(this.$_getGlobalEsp32ip());const t=this.$_getGlobalEsp32ip()+":81/";console.log(t),this.connection=new y.Z("ws://"+t,null,{debug:!1,reconnectInterval:3e3}),this.connection.onmessage=t=>{let e=new Date;if(e.getTime()-this.lastInterval>2e3?this.enable_rx_msg=!1:this.enable_rx_msg=!0,this.enable_rx_msg&&this.toggle_rx_msg){var s=JSON.parse(t.data)["canmsg"];this.sortOutCanMsg(s)}},this.connection.onopen=function(t){console.log(t),console.log("Successfully connected to the echo websocket server...")},setInterval(this.intervalFunc1000,500),setInterval(this.intervalFunc3000,3e3)},intervalFunc1000:function(){var t=new Date;this.lastInterval=t.getTime(),this.connect_status=this.connection.readyState,this.connect_status,this.timecnt=this.timecnt+1;for(let i=0;i<this.id_num;i++){var e=new Date,s=(e.getTime()-this.can_msgs[i].updatetime)/1e3;s>this.can_msgs[i].cycle&&(this.can_msgs[i].updatecount=s);for(let t=0;t<this.can_msgs[i].dlc;t++)this.can_msgs[i].updatecount_data[t]=this.can_msgs[i].updatecount_data[t]+1}},intervalFunc3000:function(){this.toggle_sort&&this.sortMsg(this.sort_target,0)},sortOutCanMsg:function(t){let e=!1;for(let n=0;n<this.idfilter_list.length;n++)if(0<this.idfilter_list[n]&&this.idfilter_list[n]<2048){e=!0;break}for(let n=1;n<t.length;n++)if((!e||this.idfilter_list.includes(t[n].id))&&t[n].id>0&&"data"in t[n]){var s,i,a=this.can_msgs.findIndex((e=>e.id===t[n].id));if(i=-1==a?this.id_num:a,s=new Date,this.can_msgs[i].id=t[n].id,this.can_msgs[i].dlc=t[n].dlc,this.can_msgs[i].cycle=t[n].cycle/1e3,this.can_msgs[i].updatetime=s.getTime(),this.can_msgs[i].updatecount=0,-1==a)this.can_msgs[i].updatecount_data=Object.assign({},this.can_msgs[this.id_num].updatecount_data),this.id_num++;else for(let e=0;e<this.can_msgs[i].dlc;e++)this.can_msgs[i].data[e]!=t[n].data[e]&&(this.can_msgs[i].updatecount_data[e]=0);this.can_msgs[i].data=Object.assign({},t[n].data)}},sortFuncId:function(t,e){return t.id<e.id?-1*this.sort_direction_id:t.id>e.id?1*this.sort_direction_id:t.cycle+t.updatecount<e.cycle+e.updatecount?-1*this.sort_direction_time:t.cycle+t.updatecount>e.cycle+e.updatecount?1*this.sort_direction_time:0},sortFuncDlc:function(t,e){return t.dlc<e.dlc?-1*this.sort_direction_dlc:t.dlc>e.dlc?1*this.sort_direction_dlc:t.id<e.id?-1*this.sort_direction_id:t.id>e.id?1*this.sort_direction_id:0},sortFuncTime:function(t,e){return t.cycle+t.updatecount<e.cycle+e.updatecount?-1*this.sort_direction_time:t.cycle+t.updatecount>e.cycle+e.updatecount?1*this.sort_direction_time:t.id<e.id?-1*this.sort_direction_id:t.id>e.id?1*this.sort_direction_id:0},sort_direction_strfunc:function(t){return-1==t?"↓":"↑"},sortMsg:function(t,e){if(-1!=t){if(this.sort_cnt++,this.sort_direction_str=["↑↓","↑↓","↑↓"],0==t){0==this.sort_target&&1==e&&(this.sort_direction_id*=-1);var s=this.can_msgs.slice(0,this.id_num).sort(this.sortFuncId);this.sort_direction_str[t]=this.sort_direction_strfunc(this.sort_direction_id)}else 1==t?(1==this.sort_target&&1==e&&(this.sort_direction_dlc*=-1),s=this.can_msgs.slice(0,this.id_num).sort(this.sortFuncDlc),this.sort_direction_str[t]=this.sort_direction_strfunc(this.sort_direction_dlc)):(2==this.sort_target&&1==e&&(this.sort_direction_time*=-1),s=this.can_msgs.slice(0,this.id_num).sort(this.sortFuncTime),this.sort_direction_str[t]=this.sort_direction_strfunc(this.sort_direction_time));this.sort_target=t;for(let t=0;t<this.id_num;t++)this.can_msgs[t]=Object.assign({},s[t])}},idFilterInput:function(t){const e=t.split(","),s=[];var i=[];e.forEach((t=>{const e=t.trim().split("-").map((t=>t.startsWith("0x")?parseInt(t,16):parseInt(t,10)));if(1===e.length)s.push(e[0]);else{const t=Math.min(e[0],e[1]),i=Math.max(e[0],e[1]);for(let e=t;e<=i;e++)s.push(e)}})),i=s.sort(((t,e)=>t-e)),this.idfilter_list=i,console.log(this.idfilter_list),this.idFilterRun()},idFilterRun:function(){var t=this.enable_rx_msg;this.enable_rx_msg=!1;let e=0;for(let i=0;i<this.id_num;i++)this.idfilter_list.includes(this.can_msgs[i].id)||(this.can_msgs[i]=Object.assign({},this.can_msg),this.can_msgs[i].id=2048,e+=1);console.log(e);var s=this.sort_direction_id;this.sort_direction_id=1,this.sortMsg(0,0),this.sort_direction_id=s,this.id_num=this.id_num-e,this.enable_rx_msg=t}}},Z=D,k=(0,d.Z)(Z,x,b,!1,null,null,null),w=k.exports,C=s(9582),S=s(4886),I=s(626),P=s(2165),$=s(7771),O=s(5085),E=s(1783),F=function(){var t=this,e=t._self._c;return e(C.Z,[e(E.Z,{attrs:{color:"gray",dark:"",flat:""}},[[e($.Z,{attrs:{"align-with-title":""},model:{value:t.tabnum,callback:function(e){t.tabnum=e},expression:"tabnum"}},[e(I.Z,[t._v(" WiFiConfig ")]),e(I.Z,[t._v(" CanRx ")]),e(I.Z,[t._v(" CanTx ")]),e(I.Z,[t._v(" Plot ")])],1)]],2),e(O.Z,{attrs:{touchless:!0},model:{value:t.tabnum,callback:function(e){t.tabnum=e},expression:"tabnum"}},[e(P.Z,[e(C.Z,[e(S.ZB,[e("wificonfig")],1)],1)],1),e(P.Z,[e(C.Z,[e(S.ZB,[e("canrecv")],1)],1)],1),e(P.Z,[e(C.Z,[e(S.ZB,[e("cantrans")],1)],1)],1)],1)],1)},L=[],N=s(4562),A=s(3863),M=s(9930),T=s(1267),G=s(4324),j=s(8419),B=s(6379),U=s(3522),H=s(3687),R=function(){var t=this,e=t._self._c;return e(g.Z,{attrs:{fluid:"","no-gutters":"",dense:"","pa-0":"","ma-0":""}},[e(m.Z,{attrs:{"no-gutters":"",dense:"","pa-10":"","ma-10":""}},[e(p.Z,{attrs:{cols:"1"},on:{click:t.save_tx_msg}},[e(G.Z,{on:{click:function(e){return e.stopPropagation(),t.save_tx_msg.apply(null,arguments)}}},[t._v(" mdi-content-save ")]),t._v(" save ")],1),e(p.Z,{attrs:{cols:"1"},on:{click:t.load_tx_msg}},[e(G.Z,{on:{click:function(e){return e.stopPropagation(),t.load_tx_msg.apply(null,arguments)}}},[t._v(" mdi-download-multiple ")]),t._v(" load ")],1),e(p.Z,{attrs:{cols:"1"}},[e(H.Z)],1),e(p.Z,{attrs:{cols:"1"}},[e(f.Z,{staticClass:"ma-0 pa-0",style:{padding:0},attrs:{label:"hex(0x**)",dense:""},model:{value:t.tx_msg_show_hex,callback:function(e){t.tx_msg_show_hex=e},expression:"tx_msg_show_hex"}})],1),e(p.Z,{attrs:{cols:"5"}},[e(H.Z)],1),e(p.Z,{attrs:{cols:"2"}},[e(f.Z,{staticClass:"ma-0 pa-0",style:{padding:0},attrs:{label:"CAN送信",dense:""},model:{value:t.runTrans_flag,callback:function(e){t.runTrans_flag=e},expression:"runTrans_flag"}})],1),e(p.Z,{attrs:{cols:"1"}},[e(f.Z,{staticClass:"ma-0 pa-0",style:{padding:0},attrs:{label:"DelConfirm",dense:""},model:{value:t.delConfirm_flag,callback:function(e){t.delConfirm_flag=e},expression:"delConfirm_flag"}})],1),e(T.Z,{staticStyle:{"overflow-y":"scroll",height:"50vh"},attrs:{xs12:""}},[e(A.Z,{staticClass:"cantrans_table",attrs:{headers:t.headers,height:"50vh","fixed-header":"",items:t.tx_msgs,"items-per-page":-1,"hide-default-footer":"",dense:""},scopedSlots:t._u([{key:"top",fn:function(){return[e(M.Z,{attrs:{"max-width":"500px"},model:{value:t.dialogDelete,callback:function(e){t.dialogDelete=e},expression:"dialogDelete"}},[e(C.Z,[e(S.EB,{staticClass:"text-h5"},[t._v("削除しますか?")]),e(S.h7,[e(H.Z),e(N.Z,{attrs:{color:"blue darken-1",text:""},on:{click:t.closeDelete}},[t._v("Cancel")]),e(N.Z,{attrs:{color:"blue darken-1",text:""},on:{click:t.deleteItemConfirm}},[t._v("OK")]),e(H.Z)],1)],1)],1)]},proxy:!0},{key:"item.edit_select",fn:function({item:s,index:i}){return[e(f.Z,{attrs:{small:""},on:{click:function(e){return t.editBtnOn(s,i)}},model:{value:s.edit_select,callback:function(e){t.$set(s,"edit_select",e)},expression:"item.edit_select"}})]}},{key:"item.trans",fn:function({item:s,index:i}){return[e(f.Z,{attrs:{small:""},on:{click:function(e){return t.transBtnOn(s,i)}},model:{value:s.trans,callback:function(e){t.$set(s,"trans",e)},expression:"item.trans"}})]}},{key:"item.canid",fn:function({item:e}){return[t._v(" "+t._s(t.toShowHexId(e.canid))+" ")]}},t._l([0,1,2,3,4,5,6,7],(function(e){return{key:`item.data.${e}`,fn:function({item:s}){return[t._v(" "+t._s(t.toShowHexData(s,e))+" ")]}}})),{key:"item.delete",fn:function({item:s}){return[e(G.Z,{attrs:{small:""},on:{click:function(e){return t.deleteItem(s)}}},[t._v(" mdi-delete ")])]}}],null,!0),model:{value:t.select_row_data,callback:function(e){t.select_row_data=e},expression:"select_row_data"}})],1),e(T.Z,{staticStyle:{height:"20vh",width:"100%",margin:"2%"},attrs:{xs12:""}},[e(m.Z,{attrs:{"align-content":"center"}},[e(p.Z,{attrs:{cols:"12",sm:"6",md:"1"}},[e(N.Z,{staticClass:"mt-3",attrs:{color:"primary",dark:"",small:"",disabled:t.now_edit},on:{click:t.new_msg}},[t._v(" +Msg ")])],1),e(p.Z,{attrs:{cols:"12",sm:"6",md:"1"}},[e(v.Z,{attrs:{label:t.toShowHexEditId(t.inputCanId[0])},on:{click:function(e){return t.numberEdit_start(t.inputCanId)},change:function(e){t.numberEdit_update(t.inputCanId),t.editCanIdCycle_update()}},model:{value:t.inputCanId[0],callback:function(e){t.$set(t.inputCanId,0,e)},expression:"inputCanId[0]"}})],1),e(p.Z,{attrs:{cols:"12",sm:"6",md:"1"}},[e(U.Z,{attrs:{items:t.select_dlc_items,label:"dlc"},model:{value:t.editData.dlc,callback:function(e){t.$set(t.editData,"dlc",e)},expression:"editData.dlc"}})],1),e(p.Z,{attrs:{cols:"12",sm:"6",md:"1"}},[e(v.Z,{attrs:{label:"cycle"},on:{click:function(e){return t.numberEdit_start(t.inputCycle)},change:function(e){t.numberEdit_update(t.inputCycle),t.editCanIdCycle_update()}},model:{value:t.inputCycle[0],callback:function(e){t.$set(t.inputCycle,0,e)},expression:"inputCycle[0]"}})],1),t._l(8,(function(s){return e(p.Z,{key:s,attrs:{cols:"12",md:"1"}},[e(C.Z,{attrs:{color:t.editDataClick_selectColor(s-1)},on:{click:function(e){return t.editDataClick(s-1,!0)}}},[e(S.ZB,{staticClass:"text-right py-1"},[t._v(" "+t._s(t.editData.data[s-1])+" "),e("br"),t._v(" 0x "+t._s(t.editData.data[s-1].toString(16))+" ")])],1)],1)}))],2),e(m.Z,{staticClass:"ma-0 pa-0"},[e(p.Z,{attrs:{cols:"3"}},[e(B.Z,{attrs:{row:""},on:{change:t.endian_select},model:{value:t.endian_type,callback:function(e){t.endian_type=t._n(e)},expression:"endian_type"}},[e(j.Z,{attrs:{label:"Intel",value:0},on:{change:t.endian_select}}),e(j.Z,{attrs:{label:"Motorola",value:1},on:{change:t.endian_select}})],1)],1),e(p.Z,{attrs:{cols:"1"}},[e(v.Z,{attrs:{label:"Factor"},on:{click:function(e){return t.numberEdit_start(t.inputPhysData_factor)},change:function(e){t.numberEdit_update(t.inputPhysData_factor),t.inputPhysData_changeFactorOffset()}},model:{value:t.inputPhysData_factor[0],callback:function(e){t.$set(t.inputPhysData_factor,0,e)},expression:"inputPhysData_factor[0]"}})],1),e(p.Z,{attrs:{cols:"1"}},[e(v.Z,{attrs:{label:"Offset"},on:{click:function(e){return t.numberEdit_start(t.inputPhysData_offset)},change:function(e){t.numberEdit_update(t.inputPhysData_offset),t.inputPhysData_changeFactorOffset()}},model:{value:t.inputPhysData_offset[0],callback:function(e){t.$set(t.inputPhysData_offset,0,e)},expression:"inputPhysData_offset[0]"}})],1),e(p.Z,{attrs:{cols:"1"}},[e(v.Z,{attrs:{label:"Step"},on:{click:function(e){return t.numberEdit_start(t.inputPhysData_step)},change:function(e){t.numberEdit_update(t.inputPhysData_step),t.inputPhysData_calc()}},model:{value:t.inputPhysData_step[0],callback:function(e){t.$set(t.inputPhysData_step,0,e)},expression:"inputPhysData_step[0]"}})],1),e(p.Z,{attrs:{cols:"3"}},[e(v.Z,{staticClass:"center-input",attrs:{label:"物�?値 ( 論理値 �? Factor + Offset )"},on:{change:t.inputPhysData_calc},scopedSlots:t._u([{key:"append",fn:function(){return[e(N.Z,{attrs:{color:"gray","x-small":""},on:{click:function(e){return t.inputPhysData_StepBtnClick(0)}}},[e(G.Z,[t._v(" mdi-plus")])],1)]},proxy:!0},{key:"prepend-inner",fn:function(){return[e(N.Z,{attrs:{color:"gray","x-small":""},on:{click:function(e){return t.inputPhysData_StepBtnClick(1)}}},[e(G.Z,[t._v(" mdi-minus")])],1)]},proxy:!0}]),model:{value:t.inputPhysData_val[0],callback:function(e){t.$set(t.inputPhysData_val,0,t._n(e))},expression:"inputPhysData_val[0]"}})],1),e(p.Z,{attrs:{cols:"1"}},[e(v.Z,{attrs:{label:"論理値"},on:{click:function(e){return t.numberEdit_start(t.inputLogiData_val)},change:function(e){t.numberEdit_update(t.inputLogiData_val),t.inputLogiData_calc()}},model:{value:t.inputLogiData_val[0],callback:function(e){t.$set(t.inputLogiData_val,0,e)},expression:"inputLogiData_val[0]"}})],1),e(p.Z,{attrs:{cols:"1"}},[e(v.Z,{attrs:{label:"論理値(hex)",readonly:""},model:{value:t.inputLogiData_hex,callback:function(e){t.inputLogiData_hex=e},expression:"inputLogiData_hex"}})],1)],1)],1)],1)],1)},W=[],q=(s(541),s(8945)),J={data:()=>({postheaders:{"Content-Type":"application/json;charset=UTF-8","Access-Control-Allow-Origin":"*"},dialog:!1,dialogDelete:!1,headers:[{text:"Edit",value:"edit_select"},{text:"ID",value:"canid"},{text:"dlc",value:"dlc"},{text:"cycle",value:"cycle"},{text:"data0",align:"right",value:"data.0"},{text:"data1",align:"right",value:"data.1"},{text:"data2",align:"right",value:"data.2"},{text:"data3",align:"right",value:"data.3"},{text:"data4",align:"right",value:"data.4"},{text:"data5",align:"right",value:"data.5"},{text:"data6",align:"right",value:"data.6"},{text:"data7",align:"right",value:"data.7"},{text:"transmit",value:"trans"},{text:"",value:"delete"}],temp_items:[0,1,2,3,4,5,6,7],select_dlc_items:[1,2,3,4,5,6,7,8],select_dlc:0,select_row_single:!0,select_row_data:[],edit_index:-1,tx_msgs:[{edit_select:!1,canid:10,dlc:3,cycle:100,data:[10,1,2,4,4,5,6,7],trans:0}],tx_msg_init:{edit_select:!1,canid:2047,dlc:8,cycle:1e3,data:[0,0,0,0,0,0,0,0]},tx_msg_show_hex:!1,runTrans_flag:!1,delConfirm_flag:!0,now_edit:!1,editedIndex:-1,editBtnStr:["New Msg","Check Msg"],editData:{canid:2047,dlc:8,cycle:1e3,data:[0,0,0,0,0,0,0,0]},editDataNoLink:{canid:"-",dlc:"-",cycle:"-",data:[0,0,0,0,0,0,0,0]},editData_dlc:-1,editDataColor:["white","white","white","white","white","white","white","white"],editDataSelect:[!1,!1,!1,!1,!1,!1,!1,!1],editData_selected_val:0,inputCanId:[0,0],inputCycle:[0,0],endian_type:1,inputPhysData_factor:[1,1],inputPhysData_offset:[0,0],inputPhysData_step:[1,0],inputPhysData_val:[0,0],OutputData:0,inputLogiData_val:[0,0],inputLogiData_hex:0,esp32url:""}),computed:{formTitle(){return-1===this.editedIndex?"New Item":"Edit Item"}},watch:{dialog(t){t||this.close()},dialogDelete(t){t||this.closeDelete()}},created(){this.initialize(),setInterval(this.intervalFunc1000,1e3),this.esp32url=this.$_getGlobalUrl()},methods:{initialize(){this.inputCanId[0]=this.editData.canid,this.inputCycle[0]=this.editData.cycle},transBtnOn(t,e){1==t.trans?this.tx_msgs[e].trans=1:this.tx_msgs[e].trans=0},editBtnOn(t,e){for(let s=0;s<8;s++)t.dlc<=s&&(t.data[s]=0);if(1==t.edit_select){this.editData=t;for(let t=0;t<this.tx_msgs.length;t++)t!=e&&(this.tx_msgs[t].edit_select=!1);this.inputCanId[0]=this.editData.canid,this.inputCycle[0]=this.editData.cycle;for(let t=0;t<8;t++)this.editDataSelect[t]=!1;this.editDataSelect.splice()}else{this.editData=this.editDataNoLink,this.editData.canid=t.canid,this.editData.dlc=t.dlc,this.editData.cycle=t.cycle;for(let e=0;e<8;e++)this.editDataSelect[e]=!1,this.editData.data[e]=t.data[e]}this.editData.data.splice(),this.now_edit=t.edit_select},editCanIdCycle_update(){this.editData.canid=this.inputCanId[0],this.editData.cycle=this.inputCycle[0]},editItem(t){this.editedIndex=this.tx_msgs.indexOf(t),this.editedItem=Object.assign({},t),this.dialog=!0},deleteItem(t){this.editedIndex=this.tx_msgs.indexOf(t),this.editedItem=Object.assign({},t),console.log(this.editedIndex),this.delConfirm_flag?this.dialogDelete=!0:this.deleteItemConfirm()},deleteItemConfirm(){this.tx_msgs.splice(this.editedIndex,1),this.closeDelete()},close(){this.dialog=!1,this.$nextTick((()=>{this.editedItem=Object.assign({},this.defaultItem),this.editedIndex=-1}))},closeDelete(){this.dialogDelete=!1,this.$nextTick((()=>{this.editedItem=Object.assign({},this.defaultItem),this.editedIndex=-1}))},save(){this.editedIndex>-1?Object.assign(this.tx_msgs[this.editedIndex],this.editedItem):this.tx_msgs.push(this.editedItem),this.close()},new_msg(){let t=Object.assign({},this.tx_msg_init);Number.isInteger(this.editData.canid)&&(t.canid=this.editData.canid),Number.isInteger(this.editData.dlc)&&(t.dlc=this.editData.dlc),Number.isInteger(this.editData.cycle)&&(t.cycle=this.editData.cycle),t.data=this.editData.data.slice(),this.tx_msgs.unshift(t)},editDataClick(t,e){this.editDataClick_select(t,e),this.editDataClick_input(),this.inputLogiData_val[0]=this.editData_selected_val,this.inputLogiData_hex=this.dec2hex_0x_string(this.inputLogiData_val[0]),this.inputPhysData_val[0]=this.input_logical2pysical(this.editData_selected_val),this.inputPhysData_calc()},editDataClick_select(t,e){1==e&&(this.editDataSelect[t]=!this.editDataSelect[t]);var s=0;if(1==this.editDataSelect[t]){s=0;for(let e=t;e<8;e++)0==this.editDataSelect[e]&&(s=1),1==s&&(this.editDataSelect[e]=!1);s=0;for(let e=t;e>=0;e--)0==this.editDataSelect[e]&&(s=1),1==s&&(this.editDataSelect[e]=!1)}if(0==this.editDataSelect[t]&&1==this.editDataSelect[t-1]&&1==this.editDataSelect[t+1])for(let i=0;i<8;i++)this.editDataSelect[i]=!1},editDataClick_selectColor(t){return 0==this.editDataSelect[t]?"white":"#ccf"},editDataClick_input(){var t,e=0,s=0;for(let i=0;i<8;i++)t=0==this.endian_type?i:7-i,1==this.editDataSelect[t]&&(s+=this.editData.data[t]<<8*e,e++);this.editData_selected_val=s},inputPhysData_calc(){this.inputLogiData_val[0]=this.input_pysical2logical(this.inputPhysData_val[0]),this.inputLogiData_hex=this.dec2hex_0x_string(this.inputLogiData_val[0]),this.editDataUpdate(this.inputLogiData_val[0])},inputLogiData_calc(){this.inputPhysData_val[0]=this.input_logical2pysical(this.inputLogiData_val[0]),this.inputLogiData_hex=this.dec2hex_0x_string(this.inputLogiData_val[0]),this.editDataUpdate(this.inputLogiData_val[0])},editDataUpdate(t){var e=0,s=0;for(let i=0;i<8;i++)s=0==this.endian_type?i:7-i,1==this.editDataSelect[s]&&(this.editData.data[s]=t>>8*e&255,e++)},input_pysical2logical(t){return Math.floor((Number(t)-Number(this.inputPhysData_offset[0]))/Number(this.inputPhysData_factor[0]))},input_logical2pysical(t){return Number(t)*Number(this.inputPhysData_factor[0])+Number(this.inputPhysData_offset[0])},inputPhysData_StepBtnClick(t){0==t?this.inputPhysData_val[0]+=Number(this.inputPhysData_step[0]):this.inputPhysData_val[0]-=Number(this.inputPhysData_step[0]),this.inputPhysData_val[0]=Number(this.inputPhysData_val[0].toFixed(5)),this.inputPhysData_val.splice(),this.inputPhysData_calc()},inputPhysData_changeFactorOffset(){this.inputPhysData_val[0]=this.inputLogiData_val[0]*this.inputPhysData_factor[0]+this.inputPhysData_offset[0]},dec2hex_0x_string(t){return"0x"+t.toString(16)},numberEdit_start(t){t[1]=t[0]},numberEdit_update(t){let e=!1;this.isString(t[0])||(t[0]=t[0].toString()),-1!==t[0].indexOf(".")?isNaN(parseFloat(t[0]))?e=!0:t[0]=parseFloat(t[0]):isNaN(parseInt(t[0]))?e=!0:t[0]=parseInt(t[0]),e&&(t[0]=t[1]),t.splice()},isString(t){return"string"===typeof t||t instanceof String},toShowHexId(t){return this.tx_msg_show_hex?t.toString(16):t.toString(10)},toShowHexEditId(t){var e;return e=this.isString(t)?parseInt(t):t,"ID: 0x"+e.toString(16)},toShowHexData(t,e){return t.dlc<=e?"":this.tx_msg_show_hex?t.data[e].toString(16):t.data[e].toString(10)},endian_select(){this.editDataClick_input(),this.inputLogiData_val[0]=this.editData_selected_val,this.inputLogiData_hex=this.dec2hex_0x_string(this.inputLogiData_val[0]),this.inputPhysData_val[0]=this.input_logical2pysical(this.editData_selected_val),console.log("test")},async sendData(){await q.Z.post(this.$_getGlobalUrl()+"post",this.tx_msgs).then((t=>{console.log(t),this.posts=t.data.posts})).catch((t=>{console.log(t)}))},save_tx_msg(){let t,e=confirm("変数の保存をしますか?�?");if(0==e)return;t=this.tx_msgs;let s=JSON.stringify(t,void 0,1);localStorage.setItem("tx_msgs",s),console.log(t)},load_tx_msg(){let t=confirm("変数のロードをしますか?�?");if(0==t)return;let e=localStorage.getItem("tx_msgs");this.tx_msgs=JSON.parse(e);for(let s=0;s<this.tx_msgs.length;s++)this.tx_msgs[s].edit_select=!1,this.tx_msgs[s].trans=0;this.now_edit=!1,console.log(this.tx_msgs)},intervalFunc1000(){this.runTrans_flag&&(this.sendData(),console.log(this.tx_msgs))}}},K=J,z=(0,d.Z)(K,R,W,!1,null,null,null),X=z.exports,Y=s(5125),Q=function(){var t=this,e=t._self._c;return e(g.Z,[e(C.Z,[e(S.EB,[t._v("Wi-Fi設�?")]),e(S.ZB,[e(Y.Z,[e(U.Z,{attrs:{label:"�?バイスID",items:[1,2,3,4,5,6,7,8,9]},model:{value:t.deviceId,callback:function(e){t.deviceId=e},expression:"deviceId"}}),e(U.Z,{attrs:{label:"接続モー�?",items:t.connectionModes},model:{value:t.connectionModeStr,callback:function(e){t.connectionModeStr=e},expression:"connectionModeStr"}}),e(m.Z,t._l(t.ipAddress,(function(s,i){return e(p.Z,{key:i},[e(v.Z,{attrs:{label:`IPアドレス${i+1}`,type:"number",min:"0",max:"255"},model:{value:t.ipAddress[i],callback:function(e){t.$set(t.ipAddress,i,e)},expression:"ipAddress[index]"}})],1)})),1),e(m.Z,t._l(t.subnetAddress,(function(s,i){return e(p.Z,{key:i},[e(v.Z,{attrs:{label:`サブネ�?トアドレス${i+1}`,type:"number",min:"0",max:"255"},model:{value:t.subnetAddress[i],callback:function(e){t.$set(t.subnetAddress,i,e)},expression:"subnetAddress[index]"}})],1)})),1),e(m.Z,t._l(t.defaultGateway,(function(s,i){return e(p.Z,{key:i},[e(v.Z,{attrs:{label:`�?フォルトゲートウェイ${i+1}`,type:"number",min:"0",max:"255"},model:{value:t.defaultGateway[i],callback:function(e){t.$set(t.defaultGateway,i,e)},expression:"defaultGateway[index]"}})],1)})),1),e(v.Z,{attrs:{label:"SSID",maxlength:"32"},model:{value:t.ssid,callback:function(e){t.ssid=e},expression:"ssid"}}),e(v.Z,{attrs:{label:"パスワー�?",type:"password",maxlength:"32"},model:{value:t.password,callback:function(e){t.password=e},expression:"password"}})],1)],1),e(S.h7,[e(p.Z,{attrs:{cols:"2"}},[e(N.Z,{on:{click:t.sendData}},[t._v("設定をESP32に送信")])],1),e(p.Z,{attrs:{cols:"3"}},[e(v.Z,{attrs:{label:"送信URL"},on:{blur:t.intervalFunc1500},model:{value:t.esp32url,callback:function(e){t.esp32url=e},expression:"esp32url"}})],1),e(p.Z,{attrs:{cols:"2"}},[e(v.Z,{attrs:{readonly:"",label:"ConnectStatus"},model:{value:t.connect_status,callback:function(e){t.connect_status=e},expression:"connect_status"}})],1)],1),e(S.h7,[e(N.Z,{on:{click:t.saveSettings}},[t._v("設定をブラウザに保�?")])],1),e(S.h7,[e(N.Z,{on:{click:t.loadSettings}},[t._v("設定をブラウザから読込")])],1)],1)],1)},V=[],tt={data(){return{deviceId:1,connectionModes:["0: APモー�?(WiFiを発信)","1: STモー�?(他�?�WiFiへ接�?)"],connectionModeStr:"",connectionMode:0,ipAddress:[0,0,0,0],subnetAddress:[0,0,0,0],defaultGateway:[0,0,0,0],ssid:"",password:"",esp32url:"",esp32ip:"",connect_status:"NON"}},created(){this.loadSettings_no_confirm(),this.esp32url=window.location.href,setInterval(this.intervalFunc1500,3e3)},methods:{getData(){const t=this.deviceId,e=this.connectionModeStr.split(":");var s=parseInt(e[0]);0!==s&&1!==s&&(s=0);const i=this.subnetAddress,a=this.defaultGateway,n=this.ipAddress,l=this.ssid,c=this.password;return{device_id:t,connect_mode:s,ip_addr0:n[0],ip_addr1:n[1],ip_addr2:n[2],ip_addr3:n[3],subnet0:i[0],subnet1:i[1],subnet2:i[2],subnet3:i[3],gateway0:a[0],gateway1:a[1],gateway2:a[2],gateway3:a[3],ssid:l,password:c}},saveSettings(){confirm("保存しますか?�?")&&localStorage.setItem("wifiSettings",JSON.stringify(this.getData()))},loadSettings(){confirm("読み込みますか?�?")&&this.loadSettings_no_confirm()},loadSettings_no_confirm(){const t=JSON.parse(localStorage.getItem("wifiSettings"));null!==t&&(console.log(t),this.deviceId=t.device_id,this.connectionModeStr=this.connectionModes[t.connect_mode],this.ipAddress[0]=t.ip_addr0,this.ipAddress[1]=t.ip_addr1,this.ipAddress[2]=t.ip_addr2,this.ipAddress[3]=t.ip_addr3,this.ipAddress.splice(),this.subnetAddress[0]=t.subnet0,this.subnetAddress[1]=t.subnet1,this.subnetAddress[2]=t.subnet2,this.subnetAddress[3]=t.subnet3,this.subnetAddress.splice(),this.defaultGateway[0]=t.gateway0,this.defaultGateway[1]=t.gateway1,this.defaultGateway[2]=t.gateway2,this.defaultGateway[3]=t.gateway3,this.defaultGateway.splice(),this.ssid=t.ssid,this.password=t.password,console.log(this.ipAddress),console.log(this.ipAddress.length))},getEsp32Url(){return this.esp32url},async sendData(){const t=this.getData();console.log(t),await q.Z.post(this.getEsp32Url()+"posteep",this.getData()).then((t=>{console.log(t),this.posts=t.data.posts,this.connect_status="Write OK"})).catch((t=>{console.log(t),this.connect_status="NG"}))},async sendCheck(){await q.Z.post(this.getEsp32Url()+"postcheck","").then((t=>{this.esp32ip=t.data,this.posts=t.data.posts,this.connect_status="OK",this.$_setGlobalEsp32ip(this.esp32ip),console.log("sendCheck postURL:",this.getEsp32Url()+"postcheck"),console.log("sendCheck getIP:",this.$_getGlobalEsp32ip())})).catch((()=>{this.connect_status="NG"}))},intervalFunc1500:function(){this.sendCheck(),this.$_setGlobalUrl(this.esp32url)}}},et=tt,st=(0,d.Z)(et,Q,V,!1,null,null,null),it=st.exports,at={components:{canrecv:w,cantrans:X,wificonfig:it},data(){return{tabnum:1,items:["web","shopping","videos","images","news"],text:"Lorem ipsum dolor sit amet, consectetur adipiscing elit, sed do eiusmod tempor incididunt ut labore et dolore magna aliqua. Ut enim ad minim veniam, quis nostrud exercitation ullamco laboris nisi ut aliquip ex ea commodo consequat.",canrx_url:"/tab?tabnum=1",tab_url:"tab"}},created:function(){this.tabnum=Number(this.$route.query.tabnum)},methods:{goToCanRx(){let t="/tab?tabnum=1";this.$router.push(t)}}},nt=at,lt=(0,d.Z)(nt,F,L,!1,null,null,null),ct=lt.exports;i.ZP.use(h.ZP);const ot=[{path:"/",component:ct},{path:"/canrx",component:w},{path:"/tab",component:ct},{path:"/cantab",component:ct}],rt=new h.ZP({mode:"history",base:"/",routes:ot});var dt=rt,ut=s(1705);i.ZP.use(ut.Z);var _t=new ut.Z({});i.ZP.config.productionTip=!1;let ht=new i.ZP({data:{$url:"no_url",$esp32ip:"no_ip"}});i.ZP.mixin({methods:{$_getGlobalUrl(){return ht.$data.$url},$_setGlobalUrl(t){ht.$data.$url=t},$_getGlobalEsp32ip(){return ht.$data.$esp32ip},$_setGlobalEsp32ip(t){ht.$data.$esp32ip=t}},computed:{$url:{get:function(){return ht.$data.$url},set:function(t){ht.$data.$url=t}},$esp32ip:{get:function(){return ht.$data.$esp32ip},set:function(t){ht.$data.$esp32ip=t}}}}),new i.ZP({router:dt,vuetify:_t,render:t=>t(_)}).$mount("#app")}},e={};function s(i){var a=e[i];if(void 0!==a)return a.exports;var n=e[i]={exports:{}};return t[i](n,n.exports,s),n.exports}s.m=t,function(){var t=[];s.O=function(e,i,a,n){if(!i){var l=1/0;for(d=0;d<t.length;d++){i=t[d][0],a=t[d][1],n=t[d][2];for(var c=!0,o=0;o<i.length;o++)(!1&n||l>=n)&&Object.keys(s.O).every((function(t){return s.O[t](i[o])}))?i.splice(o--,1):(c=!1,n<l&&(l=n));if(c){t.splice(d--,1);var r=a();void 0!==r&&(e=r)}}return e}n=n||0;for(var d=t.length;d>0&&t[d-1][2]>n;d--)t[d]=t[d-1];t[d]=[i,a,n]}}(),function(){s.n=function(t){var e=t&&t.__esModule?function(){return t["default"]}:function(){return t};return s.d(e,{a:e}),e}}(),function(){s.d=function(t,e){for(var i in e)s.o(e,i)&&!s.o(t,i)&&Object.defineProperty(t,i,{enumerable:!0,get:e[i]})}}(),function(){s.g=function(){if("object"===typeof globalThis)return globalThis;try{return this||new Function("return this")()}catch(t){if("object"===typeof window)return window}}()}(),function(){s.o=function(t,e){return Object.prototype.hasOwnProperty.call(t,e)}}(),function(){s.r=function(t){"undefined"!==typeof Symbol&&Symbol.toStringTag&&Object.defineProperty(t,Symbol.toStringTag,{value:"Module"}),Object.defineProperty(t,"__esModule",{value:!0})}}(),function(){var t={143:0};s.O.j=function(e){return 0===t[e]};var e=function(e,i){var a,n,l=i[0],c=i[1],o=i[2],r=0;if(l.some((function(e){return 0!==t[e]}))){for(a in c)s.o(c,a)&&(s.m[a]=c[a]);if(o)var d=o(s)}for(e&&e(i);r<l.length;r++)n=l[r],s.o(t,n)&&t[n]&&t[n][0](),t[n]=0;return s.O(d)},i=self["webpackChunkcan_webapp"]=self["webpackChunkcan_webapp"]||[];i.forEach(e.bind(null,0)),i.push=e.bind(null,i.push.bind(i))}();var i=s.O(void 0,[998],(function(){return s(1373)}));i=s.O(i)})();
//# sourceMappingURL=app.7b06ab3a.js.map