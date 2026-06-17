# STed2 ショートカット早見表

This is a UTF-8 reorganization of the original `sted2.hlp` (Shift-JIS
in-app help) plus the Linux X11 key bindings defined in
[`sted2/defload.c`](../sted2-2.07m+20010303/sted2/defload.c). Every
shortcut below assumes the **default** Linux key map; if you remap any
of the rows in the first table via `sted2.cnf`, substitute accordingly.

For the full original manual (in Shift-JIS), see
[`doc/original_docs/sted207/sted2.man`](../sted2-2.07m+20010303/doc/original_docs/sted207/sted2.man).
The in-app `HELP` key shows a condensed version of the same content.

## X68000 key → Linux PC keyboard

The X68000 keyboard had keys that don't exist on a PC, so the Linux
port maps them onto common keysyms. Defaults from `defload.c:189-204`,
overridable in `sted2.cnf` (search for `#key_xf1` etc.).

| X68000 key | Default Linux keysym | Typical physical key | Role |
| --- | --- | --- | --- |
| XF1 | `Alt_L` | left Alt | PLAY |
| XF2 | `Muhenkan` | left of space bar on JP layout | Track PLAY |
| XF3 | `Henkan_Mode` | right of space bar on JP layout | Resume |
| XF4 | `Hiragana_Katakana` | right of Henkan on JP layout | Pause |
| XF5 | `Alt_R` | right Alt | Stop |
| KANA (かな) | `Caps_Lock` | Caps Lock | Trace play position |
| KIGO (記号) | `F11` | F11 | Symbol input |
| TOROKU (登録) | `F12` | F12 | Register / new measure |
| INS / DEL | `Insert` / `Delete` | Insert / Delete | |
| HOME | `Home` | Home | |
| UNDO | `End` | End | |
| R.UP / R.DW (Roll Up/Down) | `Page_Up` / `Page_Down` | Page Up/Down | Page scroll |
| OPT.1 / OPT.2 | _(unset by default)_ | – | Modifier keys; see below |
| TENKEY (テンキー) | numeric keypad | dedicated numpad | Step entry |

`OPT.1` and `OPT.2` are unmapped by default. The cnf template suggests
binding them to the Windows key (keycode 121) and Menu key (keycode
126) on a 109-key keyboard via `xmodmap`:

```text
keycode 121 = Opt1
keycode 126 = Opt2
```

then in `sted2.cnf`:

```text
#key_opt1 = Opt1
#key_opt2 = Opt2
```

The 65 %-keyboard ClockworkPi DevTerm A06 has no numpad; ステップ入力で
テンキーが必須なので、USBテンキーパッドを足すか `xmodmap` で右手キー
を numpad にリマップする運用になります。

---

## トラックエディタ

### カーソル移動

| キー | 動作 |
| --- | --- |
| `←` | カーソルを左に動かす |
| `→` / `Space` | カーソルを右に動かす |
| `↑` | カーソルを上に動かす |
| `↓` | カーソルを下に動かす |
| `Ctrl+N` / `OPT.1+R.UP` | 1小節先に進む |
| `Ctrl+B` / `OPT.1+R.DW` | 1小節前に戻る |
| `Ctrl+C` / `R.UP` | 1ページ先に進む |
| `Ctrl+R` / `R.DW` | 1ページ前に戻る |
| `Ctrl+Z` | 1行ロールアップ |
| `Ctrl+W` | 1行ロールダウン |
| `Shift+R.UP` / `OPT.1+↓` | 高速アップスクロール |
| `Shift+R.DW` / `OPT.1+↑` | 高速ダウンスクロール |
| `Home` | カーソルをホームポジションに |
| `Shift+Home` | 演奏位置ジャンプ |
| `KANA` | 演奏位置トレース |

### トラック / 小節移動

| キー | 動作 |
| --- | --- |
| `Ctrl+T` | トラック番号指定で移動 |
| `OPT.1` / `Ctrl+→` | 次のトラックに移動 |
| `OPT.1` / `Ctrl+←` | 前のトラックに移動 |
| `Tab` | 小節番号指定で移動 |
| `Shift+Tab` | タグジャンプ |
| `Ctrl+Tab` | タグセット |

### ファンクションキー

| キー | 動作 |
| --- | --- |
| `F1` | 先頭行に戻す |
| `F2` | 最終行に進める |
| `F3` | トラックデータの連続置換 |
| `Shift+F3` | トラックデータの連続削除 |
| `F4` | 検索内容設定 |
| `F5` | 前方検索 |
| `Shift+F5` | 後方検索 |
| `F6` | 範囲（操作する範囲の開始行を設定） |
| `F7` | 削除（コピーバッファに移動） |
| `F8` | 複写（コピーバッファに複写） |
| `Shift+F8` | MIX 貼付（コピーバッファの内容をMIXする） |
| `F9` | 貼付（コピーバッファの内容を挿入） |
| `Shift+F9` | 反転貼付（前後を反転して挿入） |
| `F10` | カーソルのある行を二重化する |
| `Shift+F1` | ベロシティ連続設定 |
| `Shift+F2` | 最適化 |
| `Shift+F4` | NOTE 並べ替え／STEP シフト |
| `Shift+F6` | UNDO 登録 |
| `Shift+F7` | UNDO 実行 |

### 編集コマンド

| キー | 動作 |
| --- | --- |
| `S` | パートデータのセーブ |
| `L` | パートデータのロード |
| `O` | パートデータをテキスト形式で書き出す |
| `R` | コピー (Replicate) |
| `Shift+R` | 全トラック一括コピー |
| `Q` | クォンタイズ |
| `\` (¥) | ピッチベンド／コントロールチェンジ分割 |
| `Shift+\` | ノート分割 |
| `/` | スペシャルコントローラを書き込む |
| `Shift+/` | ユーザー定義エクスクルーシブのエディタを呼び出す |
| `Shift+_` / `_` | トラックエクスクルーシブエディタ |
| `Shift+[` | パートアサインを呼び出す |
| `Shift+]` | ワンタッチ ST/GT 入力の値を変更 |
| `OPT.1+F1` 〜 `F10` | ST/GT/VEL 位置で数値入力 |
| `OPT.1+A` 〜 `Z` | オプション直接選択・実行 |
| `Ctrl+]` | 対リピート検索 |

### リピート／小節記号

| キー | 動作 |
| --- | --- |
| `[` | リピート開始の記号を挿入 |
| `]` | リピート終了の記号を挿入 |
| `*` | 小節線を引く |
| `^` | 小節複写を設定 |
| `Shift+^` | 小節複写へ自動で変換する |
| `Ctrl+^` | 小節複写を展開する |

### 数値・ノート編集

| キー | 動作 |
| --- | --- |
| `+` / `>` | 数値を +1 |
| `-` / `<` | 数値を -1 |
| `Shift+>` | 数値を +10 |
| `Shift+<` | 数値を -10 |
| `=` | 数値の +/- を反転 |
| `0` 〜 `9` | 数値を編集 |
| `A` 〜 `G` | ノートを文字で編集 |
| `Return` | ノートデータを挿入 |

### 行操作

| キー | 動作 |
| --- | --- |
| `Ctrl+Y` / `Delete` | 行を削除行バッファに移動 |
| `Ctrl+L` / `End` (UNDO) | 削除行バッファの内容を挿入 |
| `KIGO` | リズムトラックパターンエディット |
| `TOROKU` | リズムトラックパターンエディット（新しい小節） |
| `Shift+TOROKU` | リズムトラックパターンエディット（新しい小節 ST 変更） |
| `Shift+@` / `@` | トラック上にコメントを書き込む |
| `K` | 小節単位の Music Key を設定・変更 |
| `X` | ワンタッチコード入力 |

### ビュー切替

| キー | 動作 |
| --- | --- |
| `V` | コントローラビジュアルエディット |
| `Shift+V` | コントローラビジュアルエディット（ワイド） |
| `Ctrl+V` | セームメジャービュー |
| `W` | ダブルトラックエディット／エディットエリア切替 |
| `Shift+W` | ダブルトラックエディット（同じ編集位置でオープン） |
| `:` | エディットモードの切り替え |
| `I` | ポイントインフォメーション |
| `Ctrl+G` | カーソル小節以降をグラフィック表示 |
| `Clear` | 編集トラック以外のグラフィックを OFF |

### 演奏

| キー | 動作 |
| --- | --- |
| `XF1` / `M` | メジャープレイ |
| `N` | ノートプレイ |
| `Shift+XF1` | ポイントプレイ（トラック単位） |
| `Ctrl+XF1` | ポイントプレイ（トラック単位小節指定） |
| `XF2` / `P` | ポイントプレイ（全トラック） |
| `Shift+XF2` | ポイントプレイ（小節指定） |
| `XF3` | 演奏再開 |
| `XF4` | 演奏一時停止 |
| `XF5` | 演奏停止 |

### その他

| キー | 動作 |
| --- | --- |
| `HELP` | コマンドヘルプを表示 |
| `Esc` | トラックセレクタに戻る（範囲設定中は設定解除） |

---

## リズムトラックエディタ

### 移動

| キー | 動作 |
| --- | --- |
| `←` / `→` / `↑` / `↓` | カーソル移動 |
| `Home` | カーソルをホームポジションに |
| `Shift+Home` | 演奏位置ジャンプ |
| `KANA` | 演奏位置トレース |
| `Tab` | 小節番号指定で移動 |
| `Ctrl+C` / `R.UP` | 次の小節のパターンを表示 |
| `Ctrl+R` / `R.DW` | 前の小節のパターンを表示 |
| `Shift+R.UP` / `Shift+R.DW` | パターンの残り半分を表示 |

### 編集

| キー | 動作 |
| --- | --- |
| `TOROKU` | 新しい小節でパターンを作る |
| `Shift+TOROKU` | 新しい小節でパターンを作る（ST 変更） |
| `+` / `>` / `-` / `<` | 数値を ±1 |
| `Shift+>` / `Shift+<` | 数値を ±10 |
| `Ctrl+Y` / `Delete` | 行を削除行バッファに移動 |
| `Ctrl+L` / `End` (UNDO) | 削除行バッファの内容を挿入 |
| `F1` | 先頭小節のパターンを表示 |
| `F2` | 最終小節のパターンを表示 |
| `F7` / `F8` / `F9` / `F10` | パターン削除／複写／貼付／行二重化 |
| `Shift+/` | リズムアサインを呼び出す |
| `Space` | 音の強さを変更（-, 1〜9 を循環） |
| `0` 〜 `9` | 音の強さを指定 |
| `Return` | ベロシティ直接指定／ステップタイム変更 |
| `Esc` | トラックエディタに戻る |

### 演奏

トラックエディタと同一（`XF1`〜`XF5`、`M`、`N`、`P`、`Shift+`、`Ctrl+` 組み合わせ）。

---

## 参考表

### ST 値（TIMEBASE = 48）

| 音符 | 割合 | ST |
| --- | --- | --- |
| 全音符 | 1 | 192 |
| 付点 2 分音符 | 1/2 + 1/4 | 144 |
| 2 分音符 | 1/2 | 96 |
| 付点 4 分音符 | 1/4 + 1/8 | 72 |
| 4 分音符 | 1/4 | 48 |
| 付点 8 分音符 | 1/8 + 1/16 | 36 |
| 8 分音符 | 1/8 | 24 |
| 付点 16 分音符 | 1/16 + 1/32 | 18 |
| 16 分音符 | 1/16 | 12 |
| 付点 32 分音符 | 1/32 + 1/64 | 9 |
| 32 分音符 | 1/32 | 6 |

### GT 値（ST = 48）

| 種別 | GT |
| --- | --- |
| タイ | 49 |
| スラー | 48 |
| レガート（テヌート） | 40–48 |
| 通常 | 30–40 |
| スタッカート | 8–24 |

### VEL 値

| 強弱記号 | 範囲 |
| --- | --- |
| `ppp` 〜 `p` (ピアニッシッシモ〜ピアノ) | 1 〜 64 |
| `mp` 〜 `mf` (メゾピアノ〜メゾフォルテ) | ≒ 64 |
| `f` 〜 `fff` (フォルテ〜フォルティッシッシモ) | 64 〜 127 |

---

## コントローラ・シンボル一覧

### 基本

| シンボル | 表示 | 内容 |
| --- | --- | --- |
| `G` / `Gnn` | PROGRAM | プログラム・チェンジ |
| `G@` | BankProg | バンク＆プログラム・チェンジ |
| `M` | MIDI CH. | MIDI チャンネル・チェンジ |
| `T` | TEMPO | テンポ・チェンジ |
| `P` | PITCH | ピッチ・ベンド |
| `C` | AFTER C. | チャンネル・アフタータッチ |
| `K` | AFTER K. | ポリフォニック・アフタータッチ |
| `L` / `Lnn` | CONTROL | コントロール・チェンジ |
| `D` | MODULAT | モジュレーション |
| `V` | VOLUME | ヴォリューム |
| `N` | PANPOT | パンポット |
| `E` | EXPRESS | エクスプレッション |
| `H` | HOLD1 | ホールド 1（ダンパーペダル） |
| `A` | RES.ALL | リセット・オール・コントローラーズ |
| `@` / `@M` | BANK MSB | バンク・セレクト (MSB) |
| `@@` / `@L` | BANK LSB | バンク・セレクト (LSB) |

### エフェクト / ペダル / RPN

| シンボル | 表示 | 内容 |
| --- | --- | --- |
| `F1` | REVERB | エフェクト 1（リバーブ・センドレベル） |
| `F3` | CHORUS | エフェクト 3（コーラス・センドレベル） |
| `F4` | DELAY | エフェクト 4（ディレイ・センドレベル） |
| `PT` | PORTA.TM | ポルタメント・タイム |
| `PO` | PORTAMEN | ポルタメント・スイッチ |
| `PC` | POR.CONT | ポルタメント・コントロール |
| `SS` | SOSTENUT | ソステヌート |
| `ST` | SOFT | ソフトペダル |
| `BR` | BREATH | ブレスコントロール |
| `EM` | DATA MSB | データ・エントリ (MSB) |
| `EL` | DATA LSB | データ・エントリ (LSB) |
| `NM` | NRPN MSB | NRPN (MSB) |
| `NL` | NRPN LSB | NRPN (LSB) |
| `RM` | RPN MSB | RPN (MSB) |
| `RL` | RPN LSB | RPN (LSB) |

### ユーザー定義／機種別エクスクルーシブ

| シンボル | 表示 | 内容 |
| --- | --- | --- |
| `U0`〜`U7` | UserExc* | ユーザー定義エクスクルーシブ |
| `X` | Tr.Exclu | トラックエクスクルーシブ |
| `B` | Rol.Base | Roland ベースアドレス |
| `R` | Rol.Para | Roland アドレス＆パラメータ |
| `I` | Rol.Dev# | Roland デバイス No.＆モデル ID |
| `S4` | MKS-7 | Roland MKS-7 Exclusive |
| `S5` | FB-01 P | YAMAHA FB-01 Parameter Change |
| `S6` | FB-01 S | YAMAHA FB-01 System Parameter Change |

未対応（X68000 オリジナルで実装無しの分）:

`S0` DX7 FUNCTION / `S1` DX VOICE PARAMETER / `S2` DX PERFORMANCE /
`S3` TX FUNCTION / `S7`-`SB` TX81Z / `SC`-`SE` DX7-2 / `SF` TX802 PCED
