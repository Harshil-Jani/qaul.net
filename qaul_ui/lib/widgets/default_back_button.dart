part of 'widgets.dart';

class DefaultBackButton extends StatelessWidget {
  const DefaultBackButton({Key? key, this.onPressed}) : super(key: key);
  final VoidCallback? onPressed;

  @override
  Widget build(BuildContext context) {
    final l18ns = AppLocalizations.of(context)!;
    return IconButton(
      splashRadius: 24,
      tooltip: l18ns.backButtonTooltip,
      icon: const Icon(Icons.arrow_back_ios_rounded),
      onPressed: onPressed != null ? onPressed! : () => Navigator.maybePop(context),
    );
  }
}
